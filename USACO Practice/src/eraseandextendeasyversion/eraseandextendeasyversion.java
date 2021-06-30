//package eraseandextendeasyversion;

import java.util.*;
import java.io.*;

public class eraseandextendeasyversion {
	
	public static char[] minimize(char[] s, int n, int k) {
		char[] ans = new char[k];
		int min = 1;
		for(int i = 2; i <= s.length; i++) {
			boolean minIsMin = true;
			for(int j = 0; j < k; j++) {
				if(s[j % min] > s[j % i]) {
					minIsMin = false;
					break;
				}
			}
			if(!minIsMin) {
				min =  i;
			}
		}
		//System.out.println(min);
		for(int i = 0; i < k; i++) {
			ans[i] = s[i % min];
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1537E1
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		char[] s = fin.readLine().toCharArray();
		char[] ans = minimize(s, n, k);
		while(true) {
			char[] newMin = minimize(ans, n, k);
			if(String.valueOf(newMin).equals(String.valueOf(ans))) {
				break;
			}
			ans = String.valueOf(newMin).toCharArray();
		}
		System.out.println(String.valueOf(ans));
	}
}
