//package twoarraysandsumoffunctions;

import java.util.*;
import java.io.*;

public class twoarraysandsumoffunctions {
	public static void main(String[] args) throws IOException {
		
		//1165E
		
		//remember that you can't rearrange elements of a, but you can arrange elements of b. This will become important later.
		//Lets say that we have an array a, and we are tasked with finding the sum of all subarrays within this array. Going through all subarrays and summing up the elements, 
		//or even constructing a pfx array, will take too long. Instead what we do is calculate how many times each value appears within the set of all subarrays, and 
		//then we add that value multiplied by the number of appearances. To calculate this, all we need to do is compute this formula: 
		//(number remaining values + 1) * (number of values passed + 1). With our original question, since the array a is fixed, we know how many times each value of a will appear in the 
		//final sum, so we can go ahead and multiply the amount of times with each value in a. From here, we pair each value of b with a value of the new array a. 
		//It is optimal to pair the highest value of a with the lowest value of b, and so on. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		Long[] a = new Long[n];
		Long[] b = new Long[n];
		long mod = 998244353;
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			a[i] = ((long) Integer.parseInt(st.nextToken())) * (((long)i + 1l) * (long)(n - i));
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			b[i] = (long) Integer.parseInt(st.nextToken());
		}
		Arrays.sort(a, Collections.reverseOrder());
		Arrays.sort(b);
		long sum = 0;
		for(long i = 0; i < n; i++) {
			a[(int)i] %= mod;
			b[(int)i] %= mod;
			sum += a[(int)i] * b[(int)i];
			//System.out.println(((i + 1) * (n - i)) + " " + a[(int)i] + " "+ b[(int)i]);
			sum %= mod;
		}
		System.out.println(sum);
	}
}
