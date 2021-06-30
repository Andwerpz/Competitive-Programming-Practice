//package pbinary;

import java.util.*;
import java.io.*;

public class pbinary {
	public static void main(String[] args) throws IOException {
		
		//1225C
		
		//just see if you can make it with m amount of p-binary numbers. You only need up to 31 p-binary numbers, since n is limited to 10^9.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int p = Integer.parseInt(st.nextToken());
		boolean isValid = false;
		int ans = 0;
		for(int i = 1; i <= 31; i++) {
			int num = n - i * p;
			int max = num;
			if(num <= 0) {
				break;
			}
			int count = 0;
			int pointer = 1;
			while(num != 0) {
				while(pointer < num) {
					pointer *= 2;
				}
				while(pointer > num) {
					pointer /= 2;
				}
				num -= pointer;
				count ++;
			}
			if(count <= i && max >= i) {
				isValid = true;
				ans = i;
				break;
			}
		}
		System.out.println(isValid? ans : -1);
	}
}
