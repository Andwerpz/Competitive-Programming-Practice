//package andorandsquaresum;

import java.util.*;
import java.io.*;

public class andorandsquaresum {
	public static void main(String[] args) throws IOException {
		
		//1368D
		
		//you want to make the largest numbers that you possibly can, since you're summing up their squares. Get the bitwise representation of each number,
		//and store the bits. We do this since the operation that we can perform on two numbers conserves the total and location of the bits involved. 
		//thus, we can just put as many bits into the first number as we can, then the same for the second number, and repeat until we run out of bits.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		StringTokenizer st = new StringTokenizer(fin.readLine());
		HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>(); //saves the powers of 2 in our inventory.
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			int power = 20;
			while(next != 0) {
				if(next - (int) (Math.pow(2, power)) >= 0) {
					next -= (int) (Math.pow(2, power));
					dict.put(power, dict.getOrDefault(power, 0) + 1);
				}
				power --;
			}
		}
		long ans = 0;
		while(true) {
			long cur = 0;
			boolean done = true;
			for(int i : dict.keySet()) {
				if(dict.get(i) != 0) {
					done = false;
					cur += Math.pow(2, i);
					dict.put(i, dict.get(i) - 1);
				}
			}
			if(done) {
				break;
			}
			ans += cur * cur;
		}
		System.out.println(ans);
	}
}
