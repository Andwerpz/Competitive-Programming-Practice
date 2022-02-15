//package andrewandstones;

import java.util.*;
import java.io.*;

public class andrewandstones {
	public static void main(String[] args) throws IOException {
		
		//1637C
		
		//notice that if a number in the middle is even, then you can automatically move all stones to the edges
		
		//the problem comes when a number is odd. notice that if a number is odd, you can make it even by moving a stone to it from
		//another number
		
		//even if a number is odd, if it is over 2, then you can move stones from it to other numbers to make them even
		
		//all you have to do is check if there is a number that exists that is greater than 1 in the middle. If that is the case, then
		//just take the sum of all numbers in the middle, and ceil divide by 2 to get the number of moves
		
		//exception is if there is only one number in the middle, then that number has to be even
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			boolean hasFirst = false;
			long ans = 0;
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
				if(i != 0 && i != n - 1) {
					if(nums[i] >= 2) {
						hasFirst = true;
					}
					ans += (long) (nums[i] / 2 + (nums[i] % 2 == 1? 1 : 0));
				}
			}
			if(n == 2) {
				hasFirst = true;
			}
			if(n == 3 && nums[1] % 2 == 1) {
				hasFirst = false;
			}
			fout.append(hasFirst? ans + "\n" : "-1\n");
		}
		System.out.print(fout);
	}
}
