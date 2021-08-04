import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;  

public class IMT2019026_main {
    public static void main(String[] args){

        int DM_hits = 0,SA_hits=0;
        int DM_count = 0,SA_count = 0;

        File[] inp_files = new File[5];
        inp_files[0] = new File("gcc.trace");       //Loading the 5 files into an arraw.
        inp_files[1] = new File("gzip.trace");      
        inp_files[2] = new File("mcf.trace");
        inp_files[3] = new File("swim.trace");
        inp_files[4] = new File("twolf.trace");

        IMT2019026_DMCache dm_CACHE = new IMT2019026_DMCache(65536);       //Instantiating a DMCache object of 65536 indeces for each file. 
        IMT2019026_SACache sa_CACHE = new IMT2019026_SACache(65536);       //Instantiating a SACache object of 65536 indeces for each file.
     
        for(int i=0;i<5;i++)
        {
            dm_CACHE.reset();                           //Resets the direct map cache before simulating on next trace file. 
            sa_CACHE.reset();                           //Resets the Set associative cache before simulating on next trace file. 
                
            DM_hits = 0;                               //Reset hit counts, total counts for each trace file
            SA_hits = 0;
            DM_count = 0;
            SA_count = 0;
            
            try 
            {
                File inp = inp_files[i];                            //Selecting the file to take input from.
                
                Scanner sc = new Scanner(inp);          
               
               //Try with Direct Map Cache

                while (sc.hasNextLine())                            
                {
                    String data = sc.nextLine();                    //New line.
                    
                    String bin_addr =  data.substring(4,data.length()-2);   //Slice off the unneccessary part from the input.

                    bin_addr = hextobin(bin_addr);                  //Convert the address from hex to binary.

                    if(dm_CACHE.check_hit(bin_addr)==1)              //Checks whether the memory access was a hit.
                    {
                        DM_hits+=1;                                 //Increments the number of hits.
                    }
                    DM_count+=1;
                }
                sc.close();

                //Try with 4-way Set Associative Cache

                sc = new Scanner(inp);                              
                while (sc.hasNextLine())                            
                {
                    String data = sc.nextLine();                    //New line.
                    
                    String bin_addr =  data.substring(4,data.length()-2);    //Slice off the unneccessary part from the input.

                    bin_addr = hextobin(bin_addr);                  //Convert the address from hex to binary.

                    if(sa_CACHE.check_hit(bin_addr)==1)              //Checks whether the memory access was a hit or not.
                    {
                        SA_hits+=1;                                 //Increments the number of hits.
                    }
                    SA_count+=1;
                }

                System.out.println("Hit Count if Direct Map Cache was used for "+ inp_files[i].getName() + ": " +DM_hits+" out of " + DM_count);
                System.out.println("Hence hit rate of DMCache for "+ inp_files[i].getName() + " is: "+((DM_hits*1.0)/DM_count)+"\n");
                System.out.println("Hit Count if 4-way Set Associative Cache was used for "+ inp_files[i].getName() + ": " +SA_hits+" out of " + SA_count);    
                System.out.println("Hence hit rate of SACache for "+ inp_files[i].getName() + " is: "+((SA_hits*1.0)/SA_count));
                
                sc.close();
            }
            catch (FileNotFoundException e) 
            {
                System.out.println("An error occurred while accessing ithe nput file.");
                e.printStackTrace();
            }
            System.out.println("-----------------------------------------------------------------");    
        }
    }

    static String hextobin(String hex)                  //Convinience function for converting hexadecimal string to binary string.   
    {
        String bin = "";
        int i=0;
        while (i < hex.length()) 
        {
            switch (hex.charAt(i)){
            case '0':
                bin += ("0000");
                break;
            case '1':
                bin += ("0001");
                break;
            case '2':
                bin += ("0010");
                break;
            case '3':
                bin += ("0011");
                break;
            case '4':
                bin += ("0100");
                break;
            case '5':
                bin += ("0101");
                break;
            case '6':
                bin += ("0110");
                break;
            case '7':
                bin += ("0111");
                break;
            case '8':
                bin += ("1000");
                break;
            case '9':
                bin += ("1001");
                break;
            case 'a':
                bin += ("1010");
                break;
            case 'b':
                bin += ("1011");
                break;
            case 'c':
                bin += ("1100");
                break;
            case 'd':
                bin += ("1101");
                break;
            case 'e':
                bin += ("1110");
                break;
            case 'f':
                bin += ("1111");
                break;
            default:
            }
            i++;
        }
        return bin;
    }
}