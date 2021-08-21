package goinghome;

import java.util.*;
import java.io.*;

public class goinghomever2 {
	
	static StreamTokenizer in;

	static int nextInt() throws IOException{
		in.nextToken();
		return (int)in.nval;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1500A
		
		//this solution was a pain to get to work. Next time, if given an option between abs() and addition, choose addition.
		
		//Notice the limit on the sizes of values. That probably has a bearing towards how you're supposed to solve the problem.
		
		//Just do a brute force search. If two pairs of values have the same sums or differences, then you can make two pairs out of them. The key observation is that at around 10^3 * 2, 
		//you will always have an answer.
		
		in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
		int n = nextInt();
		int[] nums = new int[n];
		int[][] dict = new int[5000010][2];
		for(int i = 0; i < n; i++) {
			nums[i] = nextInt();
			//.out.println(nums[i]);
		}
		boolean isValid = false;
		outer:
		for(int i = 0; i < n; i++) {
			for(int j = i + 1; j < n; j++) {
				int diff = nums[i] + nums[j];
				if(dict[diff][0] != 0) {
					if(dict[diff][0] != j + 1 && dict[diff][1] != j + 1 && dict[diff][0] != i + 1 && dict[diff][1] != i + 1) {
						isValid = true;
						int[][] ids = new int[4][2];
						ids[0] = new int[] {i + 1, nums[i]};
						ids[1] = new int[] {j + 1, nums[j]};
						int a = dict[diff][0] - 1;
						ids[2] = new int[] {a + 1, nums[a]}; 
						a = dict[diff][1] - 1;
						ids[3] = new int[] {a + 1, nums[a]};
						Arrays.sort(ids, (c, b) -> Integer.compare(c[1], b[1]));
						System.out.print("YES\n");
						System.out.println(ids[0][0] + " " + ids[3][0] + " " + ids[1][0] + " " + ids[2][0]);
						break outer;
					}
					
				}
				else if(dict[diff][0] == 0){
					dict[diff][0] = i + 1;
					dict[diff][1] = j + 1;
				}
			}
		}
		if(!isValid) {
			System.out.println("NO\n");
		}
	}
}
