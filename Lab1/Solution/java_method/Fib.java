import java.util.concurrent.TimeUnit;
import java.io.File;  // Import the File class
import java.io.FileWriter;   // Import the FileWriter class
import java.io.IOException;  // Import the IOException class to handle errors
class Fib {

    public static int fib_r(final int x) {
		if (x <= 2)
			return 1;
		return fib_r(x - 1) + fib_r(x - 2);
	}

	public static int fib_i(final int x) {
		int a = 1, b = 1, fib = 1, i = 2;
		while (i < x) {
			fib = a + b;
			a = b;
			b = fib;
			i += 1;
		}
		return fib;
	}

	public static void main(final String[] args) {
		try {
			File myObj = new File("recursion.txt");         //createing file for geting cordinates
			if (myObj.createNewFile()) {
			  System.out.println("File created: " + myObj.getName());
			} else {
			  System.out.println("File already exists.");
			}
		  } catch (IOException e) {
			System.out.println("An error occurred.");
			e.printStackTrace();
		  }

		  try {
			File myObj_i = new File("iteration.txt");         //createing file for geting cordinates
			if (myObj_i.createNewFile()) {
			  System.out.println("File created: " + myObj_i.getName());
			} else {
			  System.out.println("File already exists.");
			}
		  } catch (IOException e) {
			System.out.println("An error occurred.");
			e.printStackTrace();
		  }
		long [] R_array =new long[41];         //cordinates array 
		long [] R_array_i =new long[41];

		for(int i=0 ; i<=40;i++){              //finding recursion method run time
			final long  T1 = System.nanoTime();
			System.out.println("Fib of " + i + " = " + fib_r(i));
			final long  T2 = System.nanoTime();
			R_array[i]=T2-T1;
			System.out.println(R_array[i]);
			 
		}

		for(int i=0 ; i<=40;i++){           //  #finding iterations method run time
			final long  t1 = System.nanoTime();
			System.out.println("Fib of " + i + " = " + fib_i(i));
			final long  t2 = System.nanoTime();
			R_array_i[i]=t2-t1;
			System.out.println(R_array_i[i]);
			// System.out.println(D + "and Mill is "+ D/1000);
		}
		
		try {
			FileWriter myWriter = new FileWriter("recursion.txt");   // storing cordinates in file 
			 
			for(int i =1;i<=R_array.length;i++){
				myWriter.write(""+R_array[i-1]+"\n");
			}
			myWriter.close();
			System.out.println("Successfully wrote to the recursion.txt.");
		  } catch (IOException e) {
			System.out.println("An error occurred.");
			e.printStackTrace();
		  }

		  try {
			FileWriter myWriter_i = new FileWriter("iteration.txt"); 
			for(int i =1;i<=R_array_i.length;i++){
				myWriter_i.write(""+R_array_i[i-1]+"\n");
			}
			myWriter_i.close();
			System.out.println("Successfully wrote to the iteration.txt");
		  } catch (IOException e) {
			System.out.println("An error occurred.");
			e.printStackTrace();
		  }


    }
}

	
