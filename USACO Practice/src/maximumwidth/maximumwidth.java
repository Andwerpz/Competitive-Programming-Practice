//package maximumwidth;

import java.util.*;
import java.io.*;

public class maximumwidth {
	public static void main(String[] args) throws IOException {
		
		//1492C
		
		//use pfx and sfx. test the maximum gap in between each letter. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		char[] s = fin.readLine().toCharArray();
		char[] t = fin.readLine().toCharArray();
		int sfxPointer = n - 1;
		int pfxPointer = 0;
		int[] sfx = new int[m];
		for(int i = t.length - 1; i >= 0; i--) {
			char next = t[i];
			while(s[sfxPointer] != next) {
				sfxPointer --;
			}
			sfx[i] = sfxPointer;
			sfxPointer --;
		}
		
		int ans = 0;
		sfxPointer ++;
		for(int i = 0; i < t.length - 1; i++) {
			char next = t[i];
			while(s[pfxPointer] != next) {
				pfxPointer ++;
			}
			ans = Math.max(ans, Math.abs(pfxPointer - sfx[i + 1]));
			//System.out.println(pfxPointer + " " + sfx[i + 1]);
			pfxPointer ++;
		}
		System.out.println(ans);
	}
}
