//STEP 1. Import required packages
import java.text.SimpleDateFormat;  
import java.util.Date;  
import java.sql.*;
import java.util.*;

public class JDBC_Courier {


   static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  

   static final String DB_URL = "jdbc:mysql://localhost/courierdb?useSSL=false";

   static final String USER = "newuser";
   static final String PASS = "Dhamu@123";
   

   public static void main(String[] args) {
   Connection conn = null;
   Statement stmt = null;


// STEP 2. Connecting to the Database
   try{
      //STEP 2a: Register JDBC driver
      Class.forName(JDBC_DRIVER);
      //STEP 2b: Open a connection
      System.out.println("Connecting to database...");
      conn = DriverManager.getConnection(DB_URL,USER,PASS);
      //STEP 2c: Execute a query
      System.out.println("Creating statement...");
      stmt = conn.createStatement();
      System.out.println("--------------------Courier Management System---------------------");
      Scanner sc= new Scanner(System.in); 

        System.out.println("1. Login as student");
        System.out.println("2. Login as security");
        int inp_in= sc.nextInt();  
        sc.nextLine();
        if(inp_in == 1)
        {
            while(true)
            {
                String sql;
                System.out.println("1. Show my couriers");
                System.out.println("2. Check reached");
                System.out.println("3. Quit");
                int inp= sc.nextInt();  
                sc.nextLine();
                if(inp == 1)
                {
                    System.out.println("Enter your roll number");
                    String stu_id = sc.nextLine();
                    ResultSet rs;
                    sql = "select * from courier where ord_stu_id = \'" + stu_id + "\'"; 
                    rs = stmt.executeQuery(sql);
                    while(rs.next())
                    {
                        //Retrieve by column name
                        String courier_id  = rs.getString("courier_id");
                        String ord_stu_id = rs.getString("ord_stu_id");
                        String ord_sec_id = rs.getString("ord_sec_id");
                        String updated_at = rs.getString("updated_at");
                        String student_received = rs.getString("student_received");

                        //Display values
                        System.out.println("--------------------------");
                        System.out.println("courier_id: " + courier_id);
                        System.out.println("ord_stu_id: " + ord_stu_id);
                        System.out.println("ord_sec_id: " + ord_sec_id);
                        System.out.println("updated_at: " + updated_at);
                        System.out.println("student_received: " + student_received);
                        System.out.println("--------------------------");
                    }    
                    rs.close();
                }
                else if(inp==2)
                {
                }
                else{
                    break;
                }
            }
        }
        else if(inp_in == 2)  
        {
            while(true)
            {
                System.out.println("1. Add a new courier");
                System.out.println("2. Display all orders of a particular student");
                System.out.println("3. Display all orders registered by particular security gaurd");
                System.out.println("4. Mark a courier as recieved");
                System.out.println("5. Update a student id of a courier by courier ID");
                System.out.println("6. Delete a courier");
                System.out.println("7. Show all couriers");
                System.out.println("8. Add a new student");  
                System.out.println("9. Add a new security");  
                System.out.println("10. Add a new delivery service");  
                System.out.println("11. Quit");
                int inp= sc.nextInt();  
                sc.nextLine();
                String sql;
        
                if(inp==1)
                {
                    System.out.println("Enter the courier ID:");
                    String courier_id = sc.nextLine();
                    System.out.println("Enter the stduent roll number:");
                    String ord_stu_id = sc.nextLine();
                    System.out.println("Enter the security gaurd ID:");
                    String ord_sec_id = sc.nextLine();
                    System.out.println("Enter the delivery service ID:");
                    String service_id = sc.nextLine();
                    
                    SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd");  
                    Date date = new Date();  
                
                    String updated_at = formatter.format(date);
                    int student_received = 0;

                    sql = "insert into courier(courier_id,ord_stu_id,ord_sec_id,service_id,updated_at,student_received) VALUES (\'"+courier_id+"\', \'" + ord_stu_id+ "\', \'"+ ord_sec_id+"\', \'" + service_id + "\', \'" + updated_at + "\'," + student_received + ");";
                    stmt.executeUpdate(sql);

                    System.out.println("Inserted new record succefully");
                    
                }
                else if(inp==2)
                {
                    ResultSet rs;
                    System.out.println("Enter the roll number of the student: ");
                    String inp2 = sc.nextLine();
            
                    sql = "select * from courier where ord_stu_id = \"" + inp2+ "\"";
                    rs = stmt.executeQuery(sql);
                    while(rs.next())
                    {
                        //Retrieve by column name
                        String courier_id  = rs.getString("courier_id");
                        String ord_stu_id = rs.getString("ord_stu_id");
                        String ord_sec_id = rs.getString("ord_sec_id");
                        String updated_at = rs.getString("updated_at");
                        String student_received = rs.getString("student_received");

                        //Display values
                        System.out.println("--------------------------");
                        System.out.println("courier_id: " + courier_id);
                        System.out.println("ord_stu_id: " + ord_stu_id);
                        System.out.println("ord_sec_id: " + ord_sec_id);
                        System.out.println("updated_at: " + updated_at);
                        System.out.println("student_received: " + student_received);
                        System.out.println("--------------------------");
                    }    
                    rs.close();
                }
                else if(inp==3)
                {
                    ResultSet rs;
                    System.out.println("Enter the ID of the security: ");
                    String inp2 = sc.nextLine();
                    System.out.println("Input"+inp2);
                    sql = "select * from courier where ord_stu_id = \"" + inp2+ "\"";
                    rs = stmt.executeQuery(sql);
                    while(rs.next())
                    {
                        //Retrieve by column name
                        String courier_id  = rs.getString("courier_id");
                        String ord_stu_id = rs.getString("ord_stu_id");
                        String ord_sec_id = rs.getString("ord_sec_id");
                        String updated_at = rs.getString("updated_at");
                        String student_received = rs.getString("student_received");

                        //Display values
                        System.out.println("--------------------------");
                        System.out.println("courier_id: " + courier_id);
                        System.out.println("ord_stu_id: " + ord_stu_id);
                        System.out.println("ord_sec_id: " + ord_sec_id);
                        System.out.println("updated_at: " + updated_at);
                        System.out.println("student_received: " + student_received);
                        System.out.println("--------------------------");
                    }    
                    rs.close();
                }
                else if(inp==4)
                {
                    System.out.println("Enter the courier ID:");
                    String courier_id = sc.nextLine();
                    
                    SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd");  
                    Date date = new Date();  
                    String updated_at = formatter.format(date);
                    
                    int student_received = 1;

                    sql = "update courier set updated_at = \'" + updated_at + "\', student_received = " + student_received + " where courier_id = \'" + courier_id + "\';";
                    stmt.executeUpdate(sql);
                    System.out.println("Updated the record succefully");
                }
                else if(inp==5)
                {
                    System.out.println("Enter the courier ID:");
                    String courier_id = sc.nextLine();
                    
                    System.out.println("Enter the new student ID:");
                    String stu_id = sc.nextLine();
                    
                    SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd");  
                    Date date = new Date();  
                    String updated_at = formatter.format(date);
                    
                    int student_received = 1;

                    sql = "update courier set updated_at = \'" + updated_at + "\', ord_stu_id = \'" + stu_id + "\' where courier_id = \'" + courier_id + "\';";
                    stmt.executeUpdate(sql);
                    System.out.println("Updated the record succefully");
                }
                else if(inp==6)
                {
                    System.out.println("Enter the courier ID:");
                    String courier_id = sc.nextLine();

                    sql = "delete from courier " +"where courier_id = \"" + courier_id + "\";";
                    stmt.executeUpdate(sql);
                    System.out.println("Deleted the record succefully");
                }
                else if(inp==7)
                {
                    
                    ResultSet rs;
                    sql = "select * from courier";
                    rs = stmt.executeQuery(sql);
                    while(rs.next())
                    {
                        //Retrieve by column name
                        String courier_id  = rs.getString("courier_id");
                        String ord_stu_id = rs.getString("ord_stu_id");
                        String ord_sec_id = rs.getString("ord_sec_id");
                        String updated_at = rs.getString("updated_at");

                        //Display values
                        System.out.println("--------------------------");
                        System.out.println("courier_id: " + courier_id);
                        System.out.println("ord_stu_id: " + ord_stu_id);
                        System.out.println("ord_sec_id: " + ord_sec_id);
                        System.out.println("updated_at: " + updated_at);
                        System.out.println("--------------------------");
                    }    
                    rs.close();
                }
                else if(inp == 8)
                {
                    System.out.println("Enter the student roll number:");
                    String stu_id = sc.nextLine();
                    System.out.println("Enter the student name:");
                    String name = sc.nextLine();
                    System.out.println("Enter the mobile number:");
                    String mobile_number = sc.nextLine();
                    System.out.println("Enter the address:");
                    String address = sc.nextLine();
                    System.out.println("Enter the dob:");
                    String dob = sc.nextLine();
                    System.out.println("Enter the batch:");
                    String batch = sc.nextLine();
                    
                    sql = "insert into student(name, mobile_number, dob, address, stu_id, batch) VALUES (\'" + name + "\', \'" + mobile_number + "\', \'"+ dob + "\', \'"+ address + "\', \'"+ stu_id + "\', \'"+ batch + "\');";
                    // System.out.println(sql);
                    stmt.executeUpdate(sql);

                    System.out.println("Inserted new record succefully");
                }
                else if(inp == 9)
                {
                    System.out.println("Enter the secuirty ID:");
                    String sec_id = sc.nextLine();
                    System.out.println("Enter the secuirty name:");
                    String name = sc.nextLine();
                    System.out.println("Enter the mobile number:");
                    String mobile_number = sc.nextLine();
                    System.out.println("Enter the address:");
                    String address = sc.nextLine();
                    System.out.println("Enter the dob:");
                    String dob = sc.nextLine();
                    
                    sql = "insert into security(name, mobile_number, dob, address, sec_id) VALUES (\'" + name + "\', \'" + mobile_number + "\', \'"+ dob + "\', \'"+ address + "\', \'"+ sec_id + "\');";
                    // System.out.println(sql);
                    stmt.executeUpdate(sql);

                    System.out.println("Inserted new record succefully");
                }
                else if(inp == 10)
                {
                    System.out.println("Enter the new service ID:");
                    String serv_id = sc.nextLine();
                    System.out.println("Enter the service name:");
                    String name = sc.nextLine();
                    
                    sql = "insert into delivery_service(serv_id,name) VALUES (\'" + serv_id + "\', \'" + name + "\');";
                    // System.out.println(sql);
                    stmt.executeUpdate(sql);

                    System.out.println("Inserted new record succefully");
                }
                else{
                    break;
                }
                System.out.println("Press any key to go back");
                String temp = sc.nextLine();
            }
        }
//STEP 5: Clean-up environment
    stmt.close();
    conn.close();
	}
   
    catch(SQLException se){    	 //Handle errors for JDBC
      	se.printStackTrace();
   	}catch(Exception e){        	//Handle errors for Class.forName
      e.printStackTrace();
   }finally{				//finally block used to close resources
      try{
         if(stmt!=null)
            stmt.close();
      }catch(SQLException se2){
      }
      try{
         if(conn!=null)
            conn.close();
      }catch(SQLException se){
         se.printStackTrace();
      }					//end finally try
   }					//end try
   System.out.println("End of Code");
}					
}