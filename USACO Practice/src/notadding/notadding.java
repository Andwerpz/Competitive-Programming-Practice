//package notadding;

import java.util.*;
import java.io.*;

public class notadding {
	
	public static int gcd(int a, int b) {
		int t;
		while(b != 0) {
			t = a;
			a = b;
			b = t % b;
		}
		return a;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1627D
		
		//notice that the given values do not exceed 10^6. This, along with the fact
		//that every value is unique means that we can store the values in a boolean array
		
		//a != b, gcd(a, b) <= min(a, b)
		
		//if a number isn't included in the set, then we check if it can be made with gcd. Because of the above property, we 
		//check the largest not included numbers first, since if we checked the smallest ones, we might not have all the numbers that we 
		//potentially could have. 
		
		//one thing I couldn't figure out is that when checking, we only need to check every adjacent number. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		boolean[] v = new boolean[1000001];
		int ans = 0;
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			v[next] = true;
		}
		for(int i = v.length - 1; i >= 1; i--) {
			if(v[i]) {
				continue;
			}
			int pointer = 2;
			ArrayList<Integer> nums = new ArrayList<Integer>();
			int prev = -1;
			boolean isValid = false;
			outer:
			while(pointer * i <= v.length - 1) {
				if(!v[pointer * i]) {
					pointer += 1;
					continue;
				}
				if(prev != -1 && gcd(pointer, prev) == 1) {
					isValid = true;
					break outer;
				}
				prev = pointer;
				nums.add(pointer);
				pointer ++;
			}
			if(isValid) {
				v[i] = true;
				ans ++;
			}
		}
		System.out.println(ans);
	}
}
