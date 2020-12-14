import java.util.HashMap;
import java.util.Map;
class task4 {
	static int r;
    static int [][] cost = {{0, 3, 12, 23, 41, 6, 211, 4}, // cost from 0 
			    			{0, 0,  2,  4, 34, 4, 12, 43}, // cost from 1 
			    			{0, 0,  0,  12, 3, 5, 2,  4}, // cost from 2 
			    			{0, 0,  0,  0, 12, 4, 32, 3}, // cost from 3 
			    			{0, 0,  0,  0,  0, 4, 3, 12},  // cost from 4
			   			 	{0, 0,  0,  0,  0, 0, 3, 234},  // cost from 5
			    			{0, 0,  0,  0,  0, 0, 0, 12},  // cost from 6
			   	 			{0, 0,  0,  0,  0, 0, 0, 0}  // cost from 7 
    };
    static int iMax = 7;
    static int jMax = 7;
     
    // Just for testing, min cost from 0 to 4 should be 8.
    static int answer = 8;
    static int comp =0;
    static int comp1 =0;
    
    static Map<String,Integer> costMap = null;

    

    public static String indexToKey(int i, int j) {	 // making int value to sring 
	return Integer.toString(i) + Integer.toString(j);
    }

    public static Map<String, Integer> initHashMap() {
	Map<String,Integer> costs = new HashMap<String, Integer>();    
	for(int i=0; i < jMax-1; i++) {
	    String s = indexToKey(i, i+1); 
	    costs.put(s, cost[i][i+1]);   // updateing the cost map 
	}
	return costs; 
    }
    
    public static int minCostDynamicPro(int i, int j) {
        comp1 ++; 
	if(costMap == null) costMap = initHashMap(); // memorized value fatching part happeing   
	if(costMap.containsKey(indexToKey(i,j))) 	
	    return costMap.get(indexToKey(i,j));
	

	int min = cost[i][j];
	for(int k = i+1; k < j; k++) {
	    int tmp = minCostDynamicPro(i, k) + minCostDynamicPro(k, j);
	    if(min > tmp) min = tmp; 	    
	}
	costMap.put(indexToKey(i,j), min);  //memorizing part happing here 
	return min;
    }
	
    
    public static void main(String [] args) {
		
		for(int l=1; l<jMax; l++) {
			comp1 = 0;	    
		  	r = minCostDynamicPro(0,l);
			System.out.println("From 0 to "+l+" cost is  "+r+" Complexity=" + comp1);
		}
	/*
		if(r == answer){
			System.out.println("Your implementation might be correct");
		}else{
			System.out.println("Too bad. Try again (" + r + ")");
		}

		System.out.println("Complexity=" + comp); 
	*/

    }
}
    