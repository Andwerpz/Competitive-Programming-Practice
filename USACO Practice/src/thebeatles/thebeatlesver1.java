package thebeatles;

import java.util.*;
import java.io.*;

public class thebeatlesver1 {
	
	public static long gcd(long a, long b) {
		if(b == 0) {
			return a;
		}
		return gcd(b, a % b);
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(fin.readLine());
		int a = Integer.parseInt(st.nextToken());
		int b = Integer.parseInt(st.nextToken());
		HashSet<Long> dist = new HashSet<Long>();	//saves all possible distances from a to b
		long pointer = k - a - b;
		if(pointer == 0) {
			pointer += k;
		}
		long totalDist = n * k;
		while(pointer < totalDist + k) {
			if(!dist.contains(pointer % (totalDist))) {
				dist.add(pointer);
			}
			if(!dist.contains((pointer + 2 * b) % (totalDist))) {
				dist.add(pointer + 2 * b);
			}
			pointer += k;
		}
		pointer = a + b + k;
		if(!dist.contains((long) (a + b) % (totalDist))) {
			dist.add((long) (a + b));
		}
		if(!dist.contains((long) (a - b) % (totalDist))) {
			dist.add((long) Math.abs(a - b));
		}
		while(pointer < n * k + k) {
			if(!dist.contains(pointer % (totalDist))) {
				dist.add(pointer);
			}
			if(!dist.contains((pointer - 2 * b) % (totalDist))) {
				dist.add(pointer - 2 * b);
			}
			pointer += k;
		}
//		System.out.println(dist);
//		System.out.println(dist.size());
		long min = Long.MAX_VALUE;
		long max = 0;
		for(long i : dist) {
			//System.out.println(i);
			long cur = 0;
			if(i == 0) {
				cur = 1;
			}
			else if((totalDist) % i == 0) {
				cur = (totalDist) / i;
			}
			else {
				long temp = (totalDist * i) / gcd(totalDist, i);
//				System.out.println("TEMP: " + temp);
//				System.out.println("ANS: " + (temp / i));
				cur = temp / i;
			}
			min = Math.min(min, cur);
			max = Math.max(max, cur);
		}
		System.out.println(min + " " + max);
	}
}
