import socket
import time, sys, select
from threading import Thread

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

HOST = "127.0.0.1"
port = 3000

s.connect((HOST, port))

print("Welcome to the Quiz\n")
print("Rules:")
print("1. Start the game by pressing Y/y.The questions will start displaying after all 3 players press 'Y/y'")
print("2. You can answer the question by pressing the Buzzer(1) within 10 seconds of activation of Buzzer.")
print("3. The first one to press the buzzer will get the chance to answer and others should wait for the next question.")
print("4. If the question is answered correct, the player will be awarded 1 point else 0.5 points will be deducted")
print("5. After pressing the buzzer if player doesn't answer in 10 seconds 0.5 points will be deducted.")
print("6. The first one to reach 5 points will win.")
print("7. If no one reaches 5 points before all the questions are completed no one will win and the show will end.\n")


data = s.recv(1024)
print(str(data.decode("utf-8")))

u_name = ''
while(u_name==''):
    u_name = input("Please enter your name : ")
qno = 1
s.sendall(str.encode(u_name))
print("\nHello " + u_name + "!, ", end="")
while True:
    var = ''
    while(var==''):
        if qno == 1:
            var = input("To start the quiz, press 'Y' : ")
        else:
            var = input("To move to Q.No" + str(qno) + ", press 'Y' : ")
        var = var.lower()
    s.sendall(str.encode(var))
    data = s.recv(1024).decode("utf-8")
    if data == "restart":
        continue
    elif data == 'wait':
        print ("\nPlease wait for other players to press 'y'")
        s.sendall(b"temp")
    elif data == 'start':
        s.sendall(b"temp")
    data = s.recv(1024).decode("utf-8")     #Question
    print(data)
    print("Enter 'b' to press the buzzer\n")
    t = time.time()                         #setting initial time
    while True:
        i, o, e = select.select([sys.stdin], [], [], 0.1)   #Checks if anyone has pressed the buzzer for every 0.1 secs until 10sec
        if i:
            b = sys.stdin.readline().strip()
        else:
            b = "**"
        if b == "b":                         #Sending a messeege to server that this client has pressed the buzzer.
            message = "b"
            s.sendall(str.encode(message))          
        else:                               #Sending a messege to server that this client has not pressed the buzzer.
            s.sendall(b"n")
        flag = s.recv(1024)                 #Receiving a message from server if other clients has pressed the buzzer or not.
        if flag == b"y":                
            break
        elif flag == b"n":
            break
        if t + 10 <= time.time():           #Counting the timer.
            s.sendall(b"tup")
            flag = s.recv(1024)
            break   
    if flag == b"y":       
        print("You have pressed the buzzer\n")
        print("You have 10 seconds to answer the question. Go on!\n")
        i, o, e = select.select([sys.stdin], [], [], 10)     #If client has pressed the buzzer.He is given 10sec time to answer
        if i:
            ans = sys.stdin.readline().strip()
        else:
            ans = "**"
        s.sendall(str.encode(ans))                          #Sending the answer to server
        data = s.recv(1024)                                 #Receiving the messege if it is correct or not.
        print(data.decode("utf-8"))
        print()
        data = s.recv(1024).decode("utf-8")           #If by answering this question right, the client has won, he receives a messege here and ends the game.
        if data == "YouWon":                                    
            print("Congratulations ,You won. You scored 5 points\n")
            break
    elif flag == b"n":
        b_name = s.recv(1024).decode("utf-8")
        print("OOPS, "+ b_name+ " has already pressed the buzzer\n\n"+ "You donot receive any points for this question!\n")
        data = s.recv(1024)
        print(data.decode("utf-8"))
        print()
        data = s.recv(1024).decode("utf-8")
        if data == "Game Over":                        
            print("You Lost!!. Other user has scored 5points\n")
            break
        data = s.recv(1024)
    else:
        data = s.recv(1024)
        print(data.decode("utf-8"))
        data = s.recv(1024)
    qno += 1
    if(qno>99):
        print("There are no more questions left in the data base.\n\nThe game is declared to be a TIE")
leaderboard = []
for x in range(3):
    s.sendall(b"temp")
    data = s.recv(1024).decode("utf-8")
    leaderboard.append([data])
    s.sendall(b"temp")
    data = s.recv(1024).decode("utf-8")
    leaderboard[x].append(data) 
def Sort(alist):                                            
    alist.sort(key = lambda x: x[1],reverse = True)     #Sorting the list with respect to points is descending order.
    return alist 


leaderboard = Sort(leaderboard)
print ("      LEADERBOARD")
print("")
print("    Name        Points")
for x in range(3):
    print ('{:11}'.format(leaderboard[x][0])+" : "+'{:>7}'.format(leaderboard[x][1] +'\n'))


        


