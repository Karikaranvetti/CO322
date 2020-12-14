public class HashTableImp implements HashTable
{
   private static class ListNode 
   {
      String key;      // key Word 
      int value=0;    // data of key 
      ListNode next;      //Pointer to next node in the tempNode;
   }

   public ListNode[] Table;  //The hash Table                            
   private int count;  //The number of (key,value) pairs in the hash Table                   
   
   public HashTableImp(int BucketSize) 
   {
      Table = new ListNode[BucketSize];
   }
   
   public void insert(String key) 
   {   
      
      int bucket = hash(key); //Calculating Hash code for the given key and get bucket number
  
      ListNode tempNode=null;
      try{tempNode = Table[bucket]; //For traversing the linked tempNode}
      
      }catch(ArrayIndexOutOfBoundsException e) {
    	  System.out.println(bucket);
      }
                              
      while (tempNode != null) 
      {
         //Search the nodes in the tempNode, to see if the key already exists.
         if (tempNode.key.equals(key))
            break;
         tempNode = tempNode.next;
      }
      
      //here  this point, either tempNode is null, or tempNode.key.equals(key).
      if (tempNode != null) 
      {
         //Since tempNode is not null, we have found the key.
         //Update the value
         tempNode.value++;
      }
      else 
      {
    
         ListNode newNode = new ListNode();
         newNode.key = key;
         newNode.value++;   // incresing the value of count of occerence 
         newNode.next = Table[bucket];  // already in key to shift to linked list 
         Table[bucket] = newNode;
         count++;  //Count the newly added key.
      }
   }

public int search (String key) {
      
      int bucket = hash(key);  // At what location should the key be?
      
      ListNode temp = Table[bucket];  // For traversing the list.
      while (temp != null) {
            // Check if the specified key is in the node that
            // list points to.  If so, return the associated value.
         if (temp.key.equals(key))
            return temp.value;
         temp = temp.next;  // Move on to next node in the list.
      }  
      
      // If we get to this point, then we have looked at every
      // node in the list without finding the key.  Return
      
      return 0;  
   }
   
   
   //Test whether the specified key is already in the Table.
   public boolean containsKey(String key) 
   {   
      int bucket = hash(key);
      ListNode tempNode = Table[bucket];
      
      while (tempNode != null) 
      {
         //If we find the key in this node, return true.
         if (tempNode.key.equals(key))
            return true;
         tempNode = tempNode.next;
      }
      
      //If we get to this point, we know that the key does not exists.
      return false;
   }
   
   //Return the number of key/value pairs in the Table.
   public int getSize() 
   {
      return count;
   }

   //Compute a hash code for the key; key cannot be null.
   //The hash code depends on the size of the Table.

   private int hash(String key) 
   {
	   int h = 0;
	   for (int i = 0; i < key.length(); i++)
	   {
		   h = (89* h + key.charAt(i))%Table.length;		   
	   }	   
	   return (h%Table.length);   
   }
   
  
   public void getBucketSize(int length)  
   {
            
	   int val=0;
	   int sum = 0;
           int min = 1000000;
           int max = -1;
	   for(int i=0;i<length;i++)
	   { 		        
		   int counter=0;
		   ListNode tempNode = Table[i];
		   while(tempNode != null)
		   {		 
			   tempNode = tempNode.next;
			   counter++;
		   }
                   if(counter > max){//find maximum no of entries
                           max = counter;
                   }
                   if(counter < min){//find minimum no of entries
                           min = counter;
                   }
		   sum+=counter;
		   val=val+(int) Math.pow(counter,2);
		   System.out.println(counter);
	   }	   
	   float avg = (float)(sum/(float)length);
	   float var = (float)(val/length) - (float)(Math.pow(avg, 2));//minimum number of entries in buckets
	   System.out.println("\nTotal:"+sum);
	   System.out.println("Avg:"+avg);
	   System.out.println("Deviation:"+Math.sqrt(var));
      System.out.println("Minimum number of entries in buckets:"+min);
      System.out.println("Maximum number of entries in buckets:"+max);
   }
}
