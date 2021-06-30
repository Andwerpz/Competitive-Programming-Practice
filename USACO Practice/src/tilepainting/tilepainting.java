//package tilepainting;

import java.util.*;
import java.io.*;

public class tilepainting {
	
	public static long isPowerOfPrime(long num) {
		long limit = (long) (Math.ceil(Math.sqrt(num)));
		//System.out.println(num / 964463);
		long factor = -1;
		for(long i = 2; i <= limit + 1; i++) {
			if(factor != -1 && num != 1) {
				return 1;
			}
			while(num % i == 0) {
				
				num /= i;
				factor = i;
			}
			//System.out.println(num);
		}
		if(factor == -1) {
			return num;
		}
		return factor;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1242A
		
		//You have to make the observation that if a number is prime, then the number of different colors you can use is equal to the prime number. If a number is a power of a prime, 
		//then the number of colors is equal to that prime number. Any number will have only 1 color you can use. For example, given any non power of prime even number. By definition
		//it can be divisible by two, and since it isn't a power of 2, it can be divisible by some other number. You obviously can only use one color to color this, since youll have two 
		//'lanes' of alternating even numbers, but one odd power to combine them.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		long n = Long.parseLong(fin.readLine());
		long factor = isPowerOfPrime(n);
		System.out.println(factor);
	}
}
