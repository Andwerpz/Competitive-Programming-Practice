//package almostalldivisors;

import java.util.*;
import java.io.*;

public class almostalldivisors {
	
	public static long numDivisors(long num) {
		HashMap<Long, Long> divisors = new HashMap<Long, Long>();
		for(long i = 2; i <= num; i++) {
			while(num % i == 0) {
				num /= i;
				divisors.put((long) i, divisors.getOrDefault(i, (long) 0) + 1);
			}
		}
		int ans = 1;
		for(Long i : divisors.keySet()) {
			ans *= divisors.get(i) + 1;
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1165D
		
		//for any valid set of almost all divisors, x is equal to the smallest number times the biggest number. So for the set that you get in input, you can calculate
		//the number. Then, calculate the number of divisors that test number has. If the number of divisors is different than the input, then the input is invalid.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			HashSet<Long> divisors = new HashSet<Long>();
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long min = Integer.MAX_VALUE;
			long max = 0;
			for(int i = 0; i < n; i++) {
				long next = Integer.parseInt(st.nextToken());
				divisors.add(next);
				min = Math.min(min, next);
				max = Math.max(max, next);
			}
			long num = min * max;
			boolean isValid = true;
			while(divisors.size() != 0) {
				long cur = divisors.iterator().next();
				if(num % cur != 0) {
					isValid = false;
					break;
				}
				long next = num / cur;
				if(!divisors.contains(next) || !divisors.contains(cur)) {
					isValid = false;
					break;
				}
				divisors.remove(next);
				divisors.remove(cur);
			}
			if(n != numDivisors(num) - 2) {
				isValid = false;
			}
			fout.append(isValid? num : -1).append("\n");
		}
		System.out.print(fout);
	}
}
