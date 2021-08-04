Details of each file:
1)file1.txt : This is a database file which contains all the details of the back account.
  
2)t_file.txt : This is another database file which contains information of all the transactions made by the account holder.

3)main.c : This contains the code that displays all the options that one could do in our bank,takes inputs from user and continues further.

4)util2.c : This contains the code that displays the transactions with respect to date(sh_trans function), store and delete a user profile in transaction datafile(newst_trans and del_trans functions) and stores all the transactions of a user into transactions datafile(st_trans function).

5)util3.c : This contains the code for creating new account(create_account function) and to view the account profile(view function).    

6)util4.c : This contains the code for editing the account profile(edit function) and deleting the account(delete_account function).

7)util5.c : This contains the code for debiting amount(debit function), crediting amount(credit function), display the transaction which include maximum amount transferred(max function) and display the transaction which include minimum amount transferred(min function).

8)util6.c : This contains the code that transfers amount from one account to other account as well as a function to display the transactions in between a given range of amount(range function).

9)util7.c : This contains the code for taking loan from the bank (loan function) and a function which checks validity of the account number and password of the       user(check function).

10) All the .h files contain the declarations of the functions used.


Instructions :
-->Uncompress the compressed tar.gz folder into a directory.
-->Open the directory in terminal.
-->Compile all the files using a single command - "make all".
-->Execute the programme using "./main" command in the terminal.
-->To clean all the .o files use the command - "make clean".


NOTE : Do not make any changes to the database files.


Developers of this project:
-->Dhamodhar Reddy (IMT2019026)
-->Sri Sai Naveen (IMT2019039)
-->Kartikeya Siva Hitesh (IMT2019041)
-->Sai pallav (IMT2019520)
-->Maheedhar reddy (IMT2019074)
-->Mokshananda reddy (IMT2019054)
-->Anish sai P (IMT2019009)
