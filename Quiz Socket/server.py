import socket,time,random
from threading import Thread

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

sock.bind(("127.0.0.1",3000))
sock.listen(3)

print("Socket is now open and started listening\n")

f = open("data.txt", "r")
database = f.readlines()
l = []
for i in range(1,197):
    if(i%2==0):
        l.append(i)
random.shuffle(l)

ready_clients = 0
buzz = 0
win = 0             #Win is 1 if any client has scored more than 5 points.
ansflag = False     #Stores True if the person who pressed the buzzer has answered.
b_name = ""         #Stores the name of the player who has pressed the buzzer.
name_list = []
q_disp=0
buzz_disp = 0
def clientHandler():
    
    points = 0      #initializing the points with zero.
    flag2 = b"n"
    global b_name,win,ready_clients,name_list,buzz,l,ansflag,q_disp,buzz_disp 
   
    #Accepting the client's request for connection.
    conn1, addr = sock.accept()
    print("Connection has established with a new client\n")
    with conn1:
        time.sleep(0.2)
        conn1.sendall(b"Welcome to the quiz!!\n")  
        time.sleep(0.2)
        q_no = 0                 #The 'q_no' variable stores the question number.
        u_name = conn1.recv(1024).decode("utf-8") #The 'u_name' variable stores the user name of the client.
        time.sleep(0.2)
        name_list.append([u_name])               #Storing the name of client in a global list where other client names are also stored. 
        
        while True:                     #This loop runs until client is ready to receive next question.
            print("Waiting for "+u_name+" to be ready to receive question number " + str(q_no+1)+"\n")                            #A client is considered ready if he/she enters 'y'.  
            time.sleep(0.2)
            flag = conn1.recv(1024)            #This 'flag' variable checks whether the client is ready to receive the question or not by recieving 'y'
            time.sleep(0.2)                                   #as READY and anything other than 'y' as NOT READY.
            if flag == b"y":                    
                print(u_name+" is ready to receive question number "+str(q_no+1)+"\n")
                ready_clients += 1             #The (global)'ready_clients' variable stores the number of clients who are ready.
                                               #in other words,"the number of clients who pressed 'y'"
            else:
                time.sleep(0.2)
                conn1.sendall(b"restart")      #If the client has pressed something else other than 'y'.  
                time.sleep(0.2)
                continue                       #The server again asks the client (restarts the loop) if he/she is ready. (the client has to press 'y' if yes)
                                               
            if ((ready_clients)%3) != 0: 
                time.sleep(0.2)      #If the ready_clients is not a multiple of 3. Then server sends
                conn1.sendall(b"wait")         #'wait' message to let the client wait for other
                time.sleep(0.2)
                conn1.recv(1024)               #to be ready.
            else:
                time.sleep(0.2)
                conn1.sendall(b"start")        #If the ready_clients is a multiple of 3. Then server sends 
                time.sleep(0.2)
                conn1.recv(1024)               #'start 'messege to start the game show without waiting for others. 
            
            while ((ready_clients)%3) != 0:     #This loop waits for all the clients to be ready.For example,
                a = 1                           #If client A has pressed 'y' and others haven't, then ready_clients will be 1.
                                                #So the Client A will be in loop until ready_clients reaches 3.
            
            ansflag = False                    #The 'ansflag' variable stores 'true' is the client who has
                                               #pressed the buzzer has answered else stores 'False'
                                               #Before asking question we are reseting to 'False'.    

            rand = database[l[q_no]]           #Taking a random quesion from data base.
            n = "\nQuestion Number " + str(q_no + 1) + " : " + str(rand)
            time.sleep(0.2)
            conn1.sendall(str.encode(str(n)))  #Sending the question to the client.
            time.sleep(0.2)
            if(name_list[0][0]==u_name):
                print("Question Number "+str(q_no + 1)+" has been sent to all the clients\n")
            #This loop is to wait for clients to press the buzzer.
            while True:
                if buzz == 1:                 #If buzzer is pressed then we will send     
                    conn1.recv(1024)   
                    time.sleep(0.2)       #a messege to client to stop waiting for buzzer.    
                    conn1.sendall(b"n")
                    time.sleep(0.2)       #After sending messege we come out of loop.
                    break
                flag2 = conn1.recv(1024).decode("utf-8")  #Receiving a feedback regarding buzzer from client.
                if flag2 == "b":     
                    time.sleep(0.2)         #If the client presses the buzzer, the flag2 receives
                    conn1.sendall(b"y")
                    time.sleep(0.2)       #"b" as a messege from client
                    b_name = u_name
                    print(b_name+" has pressed the buzzer\n")
                    buzz = 1                  #Since the client pressed the buzzer we are making buzz = 1 
                    break                     #and coming out of loop.                 
                elif flag2 == "tup":  
                    time.sleep(0.2)        #If none of the clients pressed the buzzer until 10sec
                    conn1.sendall(b"tup")
                    time.sleep(0.2)     #flag2 recieves "tup" as messege which means time up.
                    break                     #Since time is over, we come out of loop.
                else:
                    time.sleep(0.2)
                    conn1.sendall(b"no")       
                    time.sleep(0.2)
            if flag2 == "b":                #If the flag2 received "b+user_name"
                data = conn1.recv(1024)        #it receives the answer from the client.
                data = data.decode("utf-8")         
                data = data + "\n"
                if data == database[l[q_no] + 1]: #If the answer is correct.
                    print(b_name + " has given the right answer after pressing the buzzer\n")
                   
                    points += 1                 #Incresing the points by 1.
                    if points >= 5:             #If the points reached 5. Then the win variable changes to 1.
                        print(u_name + " has won by scoring "+str(points+1)+"points\n")
                        print("The game has ended\n")
                        win = 1
                    time.sleep(0.1)
                    ansflag = True              
                    ans = ("\nYour answer is correct\n\n"+ "Your current score is : "+ str(points))
                elif data=="**\n":
                    print(b_name + " has not answered the question in given time after pressing the buzzer\n")
                    ansflag = True              
                    points -= 0.5
                    ans =("You have not answered the question within 10 seconds. The correct answer is "+ database[l[q_no] + 1]+"\n\nYour present score is : "+ str(points))
                else:                           #If answer is wrong
                    print(b_name + " has given the wrong answer after pressing the buzzer\n")    
                    ansflag = True              
                    points -= 0.5               #Deduction of points
                    ans = ( "\nYour answer is wrong, the correct answer is "+ database[l[q_no] + 1]+ "\n\nYour present score is : "+ str(points))
            
            elif flag2 == "tup":                #If time is up for pressing th buzzer.   
                if(name_list[0][0]==u_name):
                    print("No one has pressed the buzzer in the given time\n")
                ans = ("Seems like no one knows the right answer, The right answer is"+ database[l[q_no] + 1]+"\n")

            elif flag2=="n":                 #If client has not pressed the buzzer.
                ans = b_name

            #Sending appropriate message to the client as stored in above if conditions.
            conn1.sendall(str.encode(ans))                                           
            time.sleep(0.2)
            
            if flag2[0] == "n":        #The client have not pressed the buzzer.
                time.sleep(0.2)
                conn1.sendall(b"Please wait for the person to answer .....")
                time.sleep(0.2)
                while ansflag != True: #Waits until the ansflag reaches true.Which means, client loops
                    gameover = 0       #until person who pressed the buzzer answers or completes his time.  
                #If the the person who pressed the buzzer answers rightly and with those
                #points he wins, then the global variable 'win'changes to 1.So game ends.
                if win == 1:    
                    time.sleep(0.2) 
                    conn1.sendall(b"Game Over")
                    time.sleep(0.2) 
                    gameover = 1
                    break      #Comes out of the loop as game hence does not go below this line in this loop.
                #Remember that only the clients who haven't pressed the buzzer come into the above if condition.
                #So,the game must end also for the person who pressed the buzzer and won by answering corretly  
                time.sleep(0.2) 
                conn1.sendall(b"Go!")   
                time.sleep(0.2)        
    
            #If the player has won, the server sends 'you won' as a message to client.
            #If not sends some garbage value to client.(Here the garbage value is sent as 'temp') 
            if win == 1:       
                time.sleep(0.2) 
                conn1.sendall(b"YouWon")
                time.sleep(0.2) 
                break
            else:           
                time.sleep(0.2) 
                conn1.sendall(b"temp")
                time.sleep(0.2) 
            q_no += 1  #Increasing the question number by one in each iteration.
            if(q_no>99):
                break
            buzz = 0   #Resetting the buzz value to 0.
            q_disp = 0
            buzz_disp=0
                                     #||||||After the completion of the quiz ||||||       
        #Storing the points of the client in a list of player names.
        for x in range(3):                  
            if(name_list[x][0]==u_name):    
                name_list[x].append(points) 
        #Waiting for a small amount of time so that all the clients
        #complete storing their points into the list before sending. 
        time.sleep(0.5)   
        #Sending the points of all the players to the client to prepare leaderboard.
        for x in range(3):     
            conn1.recv(1024)                                
            conn1.sendall(str.encode(name_list[x][0]))      #Sending the player's name
            conn1.recv(1024)
            conn1.sendall(str.encode(str(name_list[x][1]))) #Sending their respective points

for i in range(0, 3):
    Thread(target=clientHandler).start()

