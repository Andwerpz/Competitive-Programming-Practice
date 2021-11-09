//package vasyaandarrays;

import java.util.*;
import java.io.*;

public class vasyaandarrays {
	public static void main(String[] args) throws IOException {
		
		//1036D
		
		//why did this one run so slow in c++, but it passed in java
		
		//just greedily look for segments of the two arrays that are equal to each other. If the sums of the arrays are equal, then there must be a way to divide the two arrays to make them equal.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		long[] a = new long[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
	    for(int i = 0; i < n; i++){
	       	a[i] = Integer.parseInt(st.nextToken());
	    }
	    int m = Integer.parseInt(fin.readLine());
	    long[] b = new long[m];
	    st = new StringTokenizer(fin.readLine());
	    for(int i = 0; i < m; i++){
	        b[i] = Integer.parseInt(st.nextToken());
	    }
	    long aSum = 0;
	    long bSum = 0;
	    int aPointer = 0;
	    int bPointer = 0;
	    int ans = 0;
	    for(int i = 0; i < n; i++){
	        aSum += a[i];
	    }
	    for(int i = 0; i < m; i++){
	        bSum += b[i];
	    }
	    //cout << "YES\n";
	    if(aSum != bSum){
	        System.out.println("-1");
	    }
	    else{
	        aSum = 0;
	        bSum = 0;
	        while(true){
	            //cout << aSum << " " << bSum << endl;;
	            if(aSum <= bSum){
	                aSum += a[aPointer];
	                aPointer ++;
	            }
	            else {
	                bSum += b[bPointer];
	                bPointer ++;
	            }
	            if(aSum == bSum){
	                ans ++;
	                //cout << "YES\n";
	            }
	            if(aPointer == n && bPointer == m){
	                break;
	            }
	        }
	        System.out.println(ans);
	    }
	}
}
