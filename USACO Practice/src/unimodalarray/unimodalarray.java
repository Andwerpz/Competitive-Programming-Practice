//package unimodalarray;

import java.util.*;
import java.io.*;

public class unimodalarray {
	public static void main(String[] args) throws IOException {
		
		//831A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		boolean increasing = true;
		boolean constant = true;
		boolean decreasing = true;
		boolean isValid = true;
		int prev = 0;
		int n = Integer.parseInt(fin.readLine());
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			if(i == 0) {
				prev = Integer.parseInt(st.nextToken());
			}
			else {
				int next = Integer.parseInt(st.nextToken());
				if(next > prev) {
					if(!increasing) {
						isValid = false;
						break;
					}
				}
				else if(next == prev) {
					increasing = false;
					if(!constant) {
						isValid = false;
						break;
					}
				}
				else {
					increasing = false;
					constant = false;
				}
				prev = next;
			}
		}
		System.out.println(isValid? "YES" : "NO");
	}
}
