
package books;

import java.io.*;
import java.util.*;

public class booksver1 {
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
    
    int max = 0;
    int a = -1;
    int b = -1;
    
    int sum = 0;
    
    while(b != n - 1) {
    	//System.out.println(a + " " + b + " " + sum + " " + books[b + 1]);
    	while(b < n - 1 && sum + books[b + 1] <= t) {
    		//System.out.println("increment b");
    		b++;
    		sum += books[b];
    	}
    	if(b - a > max) {
    		max = b - a;
    	}
    	while(a < n - 1 && b < n - 1 && sum + books[b + 1] > t) {
    		a ++;
    		sum -= books[a];
    	}
    	if(b < n - 1 && books[b + 1] > t) {
    		b = b + 1;
    		a = b + 1;
    		sum = 0;
    	}
    }
    
    System.out.println(max);
    
    fin.close();
    
	}
}