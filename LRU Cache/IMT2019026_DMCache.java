//DMCache consists of tag array and a valid array of index number of elements.
// Such that
//   index     tag    |    valid
//     0      tag[0]  |   valid[0]
//     1      tag[1]  |   valid[1]
//     2      tag[0]  |   valid[0]
//     .        .     |      .
//     .        .     |      .
//     .        .     |      .
//   65536   tag[65536] | valid[65536]

class IMT2019026_DMCache{
    
    private String[] tag;   

    private int[] valid;

    private int size;

    public IMT2019026_DMCache(int size)
    {
        this.size = size; 
        tag = new String[size];
        valid = new int[size];

        for(int i=0;i<size;i++)
        {
            valid[i] = 0;
            tag[i] = "x";
        }
    }

    public int check_hit(String bin_addr)
    {
        bin_addr = bin_addr.substring(0,bin_addr.length()-2);       //Slice off the last two bits as we are trying to only load or store a word at a time.
        
        String tag_string = bin_addr.substring(0, 14);              //Break the binary address into tag part and

        String index_string = bin_addr.substring(14,bin_addr.length());     //index part
        
        int index = Integer.parseInt(index_string,2);               //Converting index from bin to dec(for convinience)

        if(tag[index].equals(tag_string) && (valid[index]==1))      //Check if the tag in DMcache at the given index is equal to given tag and valid bit is 1.
        {
            return 1;                                               //Return 1 to indicate that this is a cache hit.
        }  
        else
        {   
            if(valid[index] == 0)  
            {
                valid[index] = 1;                                   //Change the valid bit to 1 if it was 0 previously.
            }
            tag[index] = tag_string;                                //else rewrite the tag in DMcache with the given tag.
            return 0;                                               //Return 0 to indicate that this is a cache miss.
        }
    }

    public void reset()
    {
        tag = new String[size];
        valid = new int[size];

        for(int i=0;i<size;i++)
        {
            valid[i] = 0;
            tag[i] = "x";
        }
    }

}