//SACache consists of sets of tag array and a valid array of index number of elements.
// Such that
//                      SET1                          SET2                         SET3                        SET4
//   index ||     tag    |    valid      ||     tag    |    valid     ||     tag    |    valid     ||     tag    |    valid
//     0   ||    tag[0]  |   valid[0]    ||    tag[0]  |   valid[0]   ||    tag[0]  |   valid[0]   ||    tag[0]  |   valid[0]
//     1   ||    tag[1]  |   valid[1]    ||    tag[1]  |   valid[1]   ||    tag[1]  |   valid[1]   ||    tag[0]  |   valid[0]
//     2   ||    tag[0]  |   valid[0]    ||    tag[0]  |   valid[0]   ||    tag[0]  |   valid[0]   ||    tag[0]  |   valid[0]
//     .   ||      .     |      .        ||      .     |      .       ||      .     |      .       ||      .     |      .
//     .   ||      .     |      .        ||      .     |      .       ||      .     |      .       ||      .     |      .
//     .   ||      .     |      .        ||      .     |      .       ||      .     |      .       ||      .     |      .
//   16384 || tag[16384] | valid[16384]  || tag[16384] | valid[16384] || tag[16384] | valid[16384] || tag[16384] | valid[16384]

class IMT2019026_SACache {

    private Set set1 = new Set();       //Creating 4 sets of 2 power 14 indeces each
    private Set set2 = new Set();
    private Set set3 = new Set();
    private Set set4 = new Set();
    private int[][] LRU_count;          //A 2D array that to store the how recently the set was accessed.  
    private int size;
    
    public IMT2019026_SACache(int size)
    {
        this.size = size;
        set1.reset(size/4);             //Reset all the sets in the cache. i.e sets all the tags to dont cares and valid bits to 0.
        set2.reset(size/4);
        set3.reset(size/4);
        set4.reset(size/4);

        LRU_count = new int[4][size/4];
        
        for(int i=0;i<size/4;i++)       //Initialize the LRU_count of all the elements to -1.
        {
            LRU_count[0][i] = -1;
            LRU_count[1][i] = -1;
            LRU_count[2][i] = -1;
            LRU_count[3][i] = -1;
        }
    }

    public int check_hit(String bin_addr)
    {
        bin_addr = bin_addr.substring(0,bin_addr.length()-2);   //Slice off the last two bits as we are trying to only load or store a word at a time.
        
        String tag_string = bin_addr.substring(0, 16);          //Break the binary address into tag part and
        
        String index_string = bin_addr.substring(16,bin_addr.length()); //index part.
        
        int index = Integer.parseInt(index_string,2);           //Converting index from bin to dec(for convinience)
        
        index = index%(65536/4);                         // Since we have 4 sets, the number of blocks also reduces by 4 times. 

        if(set1.valid[index] == 1 && set1.tag[index].equals(tag_string))           //Check if the valid bit is 1 and whether the tag in any of 4sets of the SAcache at the given index is equal to given tag .
        {
            LRU_count[0][index]=0;                                                 //Accesed now, hence LRU count is zero.  
            if( LRU_count[1][index]!=-1 )    LRU_count[1][index]++;                 
            if( LRU_count[2][index]!=-1 )    LRU_count[2][index]++;
            if( LRU_count[3][index]!=-1 )    LRU_count[3][index]++;
            return 1;                       
        }
        else if(set2.valid[index] == 1 && set2.tag[index].equals(tag_string) )
        {
            if( LRU_count[0][index]!=-1 )    LRU_count[0][index]++;
            LRU_count[1][index]=0;                                                 //Accesed now, hence LRU count is zero.
            if( LRU_count[2][index]!=-1 )    LRU_count[2][index]++;
            if( LRU_count[3][index]!=-1 )    LRU_count[3][index]++;
            return 1;
        }  
        else if( set3.valid[index] == 1 &&  set3.tag[index].equals(tag_string) )
        {
            if( LRU_count[0][index]!=-1 )    LRU_count[0][index]++;                 //Increase LRU_count only if the there was already some data in that index of that set. 
            if( LRU_count[1][index]!=-1 )    LRU_count[1][index]++;
            LRU_count[2][index] = 0;                                                //Accesed now, hence LRU count is zero.
            if( LRU_count[3][index]!=-1 )    LRU_count[3][index]++;
            return 1;           
        }
        else if( set4.valid[index] == 1 && set4.tag[index].equals(tag_string) )
        {
            if( LRU_count[0][index]!=-1 )    LRU_count[0][index]++;
            if( LRU_count[1][index]!=-1 )    LRU_count[1][index]++;
            if( LRU_count[2][index]!=-1 )    LRU_count[2][index]++;
            LRU_count[3][index] = 0;                                                //Accesed now, hence LRU count is zero.
            return 1;
        }
        else
        {                                               //Else check the least recent used set and replace the memory in this set with the new memory and tag.
            switch(get_least_recent(index)){
                case 1:
                    set1.tag[index] = tag_string;
                    set1.valid[index] = 1;
                    
                    LRU_count[0][index] = 0;                                        //Accesed now, hence LRU count is zero.
                    if( LRU_count[1][index]!=-1 )    LRU_count[1][index]++;
                    if( LRU_count[2][index]!=-1 )    LRU_count[2][index]++;
                    if( LRU_count[3][index]!=-1 )    LRU_count[3][index]++;
                    break;
                case 2:
                    set2.tag[index] = tag_string;
                    set2.valid[index] = 1;
                    
                    LRU_count[1][index] = 0;                                        //Accesed now, hence LRU count is zero.
                    if( LRU_count[0][index]!=-1 )    LRU_count[0][index]++;
                    if( LRU_count[2][index]!=-1 )    LRU_count[2][index]++;
                    if( LRU_count[3][index]!=-1 )    LRU_count[3][index]++;
                    break;
                case 3:
                    set3.tag[index] = tag_string;
                    set3.valid[index] = 1;
                    
                    LRU_count[2][index] = 0;                                        //Accesed now, hence LRU count is zero.
                    if( LRU_count[0][index]!=-1 )    LRU_count[0][index]++;
                    if( LRU_count[1][index]!=-1 )    LRU_count[1][index]++;
                    if( LRU_count[3][index]!=-1 )    LRU_count[3][index]++;
                    break;
                case 4:
                    set4.tag[index] = tag_string;
                    set4.valid[index] = 1;
                    
                    LRU_count[3][index] = 0;                                        //Accesed now, hence LRU count is zero.
                    if( LRU_count[1][index]!=-1 )    LRU_count[1][index]++;
                    if( LRU_count[2][index]!=-1 )    LRU_count[2][index]++;
                    if( LRU_count[0][index]!=-1 )    LRU_count[0][index]++;
                    break;
                default:
                    break;
            }
            return 0;
        }
    }

    private int get_least_recent(int index)
    {                                           //We were using LRU_count to indicate how less recently the set was accessed. That is 0 for most recent. 
        int max = -1;                           //Hence least recent of all the sets will have maximum LRU count.
        int maxset = -1;
        for(int i=0;i<4;i++)
        {
            if(LRU_count[i][index] == -1)        //LRU count is -1 if that set is not at all used till now.
            {
                return i+1;                     //If any of the sets was not at all used till now. Then we need to write to that set instead of the least recent one.  
            }
            if(LRU_count[i][index] > max)
            {
                maxset = i;
                max = LRU_count[i][index];
            }
        }   
        return maxset+1;                        //Returns the set which has maximum LRU count. 
    }

    public void reset()
    {
        set1.reset(size/4);
        set2.reset(size/4);
        set3.reset(size/4);
        set4.reset(size/4);
    }
}
class Set                           //Individual set. Which together along with other three sets forms 4 - way SA cache. 
{
    public String[] tag ;

    public int[] valid ;

    public void reset(int size)     //Just resets valid and tag bits.
    {
        tag = new String[size];
        valid = new int[size];
        for(int i=0;i<size;i++)
        {
            valid[i] = 0;       //valid --> 0
            tag[i] = "x";       //tag --> dont care
        }
    }
}
