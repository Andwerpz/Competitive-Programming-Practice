//package strangedefinition;

import java.util.*;
import java.io.*;

public class strangedefinition {
	public static void main(String[] args) throws IOException {
		
		//1471D
		
		//Notice that in order for two numbers to be adjacent, both of the numbers structures need to be something like: gcd * perfect square. The square can be anything. This means 
		//within the prime factors, the gcd must be primes of odd quantity, since if they were of even quantity, then they would make up the perfect square portion. This also
		//means that all numbers with the same single primes are adjacent. 
		
		//we can precompute each numbers adjacent group by dividing all numbers by square wherever possible. Then, we have to deal with the time aspect of the problem. Notice that odd
		//quantity groups of adjacent numbers end up with the same single primes no matter how many times they are multiplied together, while even quantity groups end up with no single primes.
		//this is because they have an even quantity of numbers, and the gcd can just find a pair within itself. So for time 0, the largest group will be the beauty score, and for all times past 0, 
		//you also have to factor in the larger group made up of the combination of all even quantity groups.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		int[] factors = new int[1000001];
		for(int i = 0; i < factors.length; i++) {
			factors[i] = i;
		}
		for(int i = 2; i < factors.length; i++) {
			int square = i * i;
			//System.out.println(square);
			if(square < factors.length) {
				for(int j = square; j < factors.length; j += square) {
					while(factors[j] % square == 0) {
						factors[j] /= square;
					}
				}
			}
			else {
				break;
			}
		}
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int max = 0;
			HashMap<Integer, Integer> groups = new HashMap<Integer, Integer>();
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				int which = factors[next];
				groups.put(which, groups.getOrDefault(which, 0) + 1);
				max = Math.max(max, groups.get(which));
			}
			int sumOfEvens = 0;
			for(int i : groups.keySet()) {
				if(groups.get(i) % 2 == 0) {
					sumOfEvens += groups.get(i);
				}
				else if(i == 1) {
					sumOfEvens += groups.get(i);
				}
			}
			int q = Integer.parseInt(fin.readLine());
			for(int i = 0; i < q; i++) {
				Long next = Long.parseLong(fin.readLine());
				if(next == 0) {
					fout.append(max).append("\n");
				}
				else {
					fout.append(Math.max(max, sumOfEvens)).append("\n");
				}
			}
		}
		System.out.print(fout);
	}
}
