//package squarefreedivisioneasyversion;

import java.util.*;
import java.io.*;

public class squarefreedivision {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		ArrayList<Integer> primes = new ArrayList<Integer>();
		boolean[] isPrime = new boolean[4000];
		Arrays.fill(isPrime, true);
		for(int i = 2; i < isPrime.length; i++) {
			if(isPrime[i]) {
				primes.add(i);
				for(int j = i * 2; j < isPrime.length; j += i) {
					isPrime[j] = false;
				}
			}
		}
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				int val = 1;
				for(int j = 0; j < primes.size() && primes.get(j) <= next; j++) {
					boolean add = false;
					int prime = primes.get(j);
					while(next % prime == 0) {
						next /= prime;
						add = !add;
					}
					if(add) {
						val *= prime;
					}
				}
				if(next != 1) {
					val *= next;
				}
				nums[i] = val;
			}
			int ans = 1;
			HashSet<Integer> dict = new HashSet<Integer>();
			int pointer = 0;
			for(int i = 0; i < n; i++) {
				//System.out.print(nums[i] + " ");
				int next = nums[i];
				if(dict.contains(next)) {
					dict.clear();
					ans ++;
				}
				dict.add(next);
			}
			//System.out.println();
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
