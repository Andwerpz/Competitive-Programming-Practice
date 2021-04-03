
package multipleof2019;

import java.io.*;
import java.util.*;

public class multipleof2019ver1 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    String s = st.nextToken();
    int n = s.length();
    int m = 2019;
    
    int sfx = 0;	//use suffix sums to get the actual represented value of the set of numbers in the string.
    int power = 1;
    int[] dict = new int[m];
    dict[0] = 1;	//representing subtracting an empty subarray
    long ans = 0;
    
    for(int i = n - 1; i >= 0; i--) {
    	int digit = Integer.parseInt(s.charAt(i) + "");
    	sfx = (sfx + (digit * power)) % m;
    	power = (10 * power) % m;
    	ans += dict[sfx];
    	dict[sfx] ++;
    }
    
    System.out.println(ans);
    fin.close();
    
	}
}