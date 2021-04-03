
package books;

import java.io.*;
import java.util.*;

public class booksver2 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int t = Integer.parseInt(st.nextToken()); 

    int[] books = new int[n];
    st = new StringTokenizer(fin.readLine());
    for(int i = 0; i < n; i++) {
    	books[i] = Integer.parseInt(st.nextToken());
    }
    
    //Arrays.sort(books);
    
    int a = 0;
    int b = 0;
    int max = 0;
    if(books[0] <= t) {
    	max = 1;
    }
    int sum = books[0];
    
    boolean done = false;
    
    while(b != n - 1) {
    	//System.out.println(a + " " + b);
    	
    	if(b < n - 1 && sum + books[b + 1] <= t) {
    		b++;
    		sum += books[b];
    	}
    	else {
    		a++;
    		sum -= books[a - 1];
    	}
    	if(b - a + 1 > max) {
    		max = b - a + 1;
    	}
    	//System.out.println(a + " " + b + " " + sum);
    }
    
    System.out.println(max);
    fin.close();
    
	}
}