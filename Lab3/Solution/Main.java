import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Main  extends HashTableImp
{	
	public Main (int initialSize) 
	{
		super(initialSize);		
	} 

	public static void main(String[]args)
	{		
		String line="";
		int hashTableSize=0;		
		Main  hashMap = null;
		
		//Extracting number of buckets from command line
		if(args.length == 2)
		{
			hashTableSize = Integer.valueOf(args[0]);
			hashMap = new Main (hashTableSize);
			
			//Reading from Text Files
			String fileName = args[1];
			try(BufferedReader br = new BufferedReader(new FileReader(fileName)))
			{
				while((line = br.readLine())!=null)
				{
					//Converting all non-alphanumberic characters to whitespace						
					String text = line.replaceAll("[^A-Za-z0-9]"," ");
					//split lines between whitespaces
					String tokens[] = text.split("\\s+");
					for(String s:tokens)
					{
						//insert strings to hash table
						hashMap.insert(s);								
					}
				}			
			}		
			catch (FileNotFoundException e)
			{
				System.out.println("File does not exists");
				System.exit(0);
			}
			catch (IOException e) 
			{
				System.out.println("File reading failed");
				System.exit(0);
			}		
			//Print overall information of contents in the hash table and it's distribution
			hashMap.getBucketSize(hashTableSize);
			System.out.println();
				
			try(Scanner inval = new Scanner(System.in))
			{				
				String key;
				do 
				{
					//Prompting user to enter a key to search from the hash table
					System.out.println("Enter a key to search: ");
					key = inval.nextLine();
					System.out.println("Value: "+hashMap.search(key));
				}
				while(!key.equals("quit"));
			}				
		}		
		else
		{
		System.out.println("\nUsage:for compiling via terminal");
		System.out.println("Insert-> Java Main  [number of buckets needed] [filename]");
		System.out.println("Ex-> Java Main  30 sample-text1.txt");	
		System.out.println("To quit from loop-> quit");
		}
	}
	
	 
}
