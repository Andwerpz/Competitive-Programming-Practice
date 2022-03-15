//package madokandthebestschoolinrussia;

import java.util.*;
import java.io.*;

public class madokaandthebestschoolinrussia {
	public static void main(String[] args) throws IOException {
		
		//1647D
		
		//notice that all beautiful numbers must be good, meaning that they must be divisible by d,
		//and they must not be divisible by d^2. 
		
		//this is because when multiplying 2 good numbers, they are always divisible by d^2, so if
		//a number isn't divisible by d^2, then it can't be the product of 2 good numbers. 
		
		//if x isn't divisible by d^2, then it can't be a product of 2 beautiful numbers, since beautiful
		//numbers must be divisible by d. 
		
		//from here, we can see that x = a * d^b. 
		
		//if d is prime, then we just have to check for factors of a. If a has 2 or more factors, then
		//print YES, else NO
		
		//if d isn't prime, but has 1 factor, then we know it's a square, cube, ect...
		//do the same thing as prime number, but this time, if a doesn't have more than 1 factor, then we can 
		//check if breaking apart a d will allow us to do it anyways,
		
		//else we know d is a composite number. 
		//just have to check for factors of a, just like in the prime case.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long x = Integer.parseInt(st.nextToken());
			long d = Integer.parseInt(st.nextToken());
			long dSquare = d * d;
			if(x % dSquare != 0) {
				fout.append("NO\n");
				continue;
			}
			HashMap<Long, Integer> factors = new HashMap<>();	//factors of d
			long temp = d;
			for(long i = 2; i <= (long) Math.sqrt(d); i++) {
				while(temp % i == 0) {
					temp /= i;
					factors.put(i, factors.getOrDefault(i, 0) + 1);
					factors.put(d / i, factors.getOrDefault(d / i, 0) + 1);
				}
			}
			int b = 0;
			temp = x;
			while(temp % d == 0) {
				temp /= d;
				b++;
			}
			//System.out.println(factors);
			if(factors.size() == 0) {	//d is prime
				//System.out.println("prime");
				x /= (long) Math.pow(d, b);
				//System.out.println(x);
				long oX = x;
				int fCnt = 0;
				for(long i = 2; i <= (long) Math.sqrt(x); i++) {
					while(x % i == 0) {
						x /= i;
						fCnt ++;
						if(i * i != oX) {
							fCnt ++;
						}
					}
				}
				//System.out.println(fCnt);
				fout.append(fCnt >= 2? "YES\n" : "NO\n");
				continue;
			}
			if(factors.size() == 1) {	//d is a perfect square, cube, ect..
				long f = factors.keySet().iterator().next();
				temp = x;
				int amt = 0;
				while(temp % f == 0) {
					temp /= f;
					amt ++;
				}
				int times = amt / b;	//amt of times this factor goes into x.
				long oX = temp;
				int fCnt = amt % b;
				//System.out.println(fCnt + " " + temp);
				for(long i = 2; i <= (long) Math.sqrt(x); i++) {
					while(temp % i == 0) {
						temp /= i;
						fCnt ++;
						if(i * i != oX) {
							fCnt ++;
						}
					}
				}
				if(temp > 1) {
					fCnt ++;
				}
				if(fCnt >= 2) {
					fout.append("YES\n");
					continue;
				}
				//System.out.println(times + " " + amt);
				//System.out.println((int) Math.ceil((double) amt / (double) (b - 1)) + " " + b);
				if((int) Math.ceil((double) amt / (double) (b - 1)) >= times * 2) {
					fout.append("NO\n");
					continue;
				}
				fout.append("YES\n");
				continue;
			}
			//System.out.println("composite");
			//d is composite
			if(b >= 3) {
				fout.append("YES\n");
				continue;
			}
			x /= (long) Math.pow(d, b);
			//System.out.println(x);
			long oX = x;
			int fCnt = 0;
			for(long i = 2; i <= (long) Math.sqrt(x); i++) {
				while(x % i == 0) {
					x /= i;
					fCnt ++;
					if(i * i != oX) {
						fCnt ++;
					}
				}
			}
			//System.out.println(fCnt);
			fout.append(fCnt >= 2? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}
