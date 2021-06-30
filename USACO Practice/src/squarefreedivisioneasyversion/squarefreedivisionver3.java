package squarefreedivisioneasyversion;

import java.util.*;
import java.io.*;

public class squarefreedivisionver3 {
	public static void main(String[] args) throws IOException {
		
		//1497E1
		
		//since we only care about whether if two numbers multiplied together make a perfect square, a number represented like this: a = p1^q1 * p2^q2 ... * pn^qn
		//can be represented like this: a = p1^(q1 % 2) * p2^(q2 % 2) ... * pn^(qn % 2). This works since if a number is a perfect square, all of it's prime
		//factors must be even, and if two numbers multiply together to make a perfect square, then they must be equal in the second method of representation.
		//From here, just represent every number with the second method, and do a simple two pointer search to make the largest subsequences of unique numbers.
		
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
