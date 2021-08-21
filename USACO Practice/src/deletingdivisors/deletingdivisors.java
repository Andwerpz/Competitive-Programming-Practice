//package deletingdivisors;

import java.util.*;
import java.io.*;

public class deletingdivisors {
	public static void main(String[] args) throws IOException {
		
		//1537D
		
		//notice that if on your turn, if n is odd, then you must subtract an odd divisor, making the number even for the next person. Also, notice that when subtracting the odd divisor, 
		//the resulting number will never be a power of 2, since the resulting number will always be divisible by that odd divisor. This means that your opponent can always subtract an odd 
		//divisor, since on their turn, the number is even. This means that if the number is odd on your turn, then you will always lose, and if the number is even on your turn
		//and is not a power of 2, then you will always win. 
		
		//this leaves just the numbers of powers of 2. Notice that the optimal move is to always subtract the largest divisor, so to make the resulting number another power of 2. 
		//if you were to make the resulting number not a power of 2, then it will be even, and the other player will always win. So the winning strategy is to keep dividing by 2 
		//until one player can't make any more moves.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		HashSet<Long> powersOfTwo = new HashSet<Long>();
		long pointer = 2;
		while(pointer < Integer.MAX_VALUE) {
			powersOfTwo.add(pointer);
			pointer *= 2;
		}
		while(t-- > 0) {
			long n = Integer.parseInt(fin.readLine());
			if(powersOfTwo.contains(n)) {
				boolean aliceTurn = true;
				while(true) {
					if(n == 2) {
						break;
					}
					n /= 2;
					aliceTurn = !aliceTurn;
				}
				fout.append(aliceTurn? "Bob\n" : "Alice\n");
			}
			else if(n % 2 == 0) {
				fout.append("Alice\n");
			}
			else {
				fout.append("Bob\n");
			}
		}
		System.out.print(fout);
	}
}
