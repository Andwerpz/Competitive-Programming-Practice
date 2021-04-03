//package queueattheschool;

import java.util.*;
import java.io.*;

public class queueattheschool {
	public static void main(String[] args) throws IOException {
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		
		int n = Integer.parseInt(st.nextToken());
		int t = Integer.parseInt(st.nextToken());
		char[] qu = fin.readLine().toCharArray();
		
		while(t -- > 0) {
			
			for(int i = 0; i < n - 1; i++) {
				if(qu[i] == 'B' && qu[i + 1] == 'G') {
					char temp = qu[i];
					qu[i] = qu[i + 1];
					qu[i + 1] = temp;
					i++;
				}
			}
			
		}
		
		String s = new String(qu);
		System.out.println(qu);
		
	}
}
