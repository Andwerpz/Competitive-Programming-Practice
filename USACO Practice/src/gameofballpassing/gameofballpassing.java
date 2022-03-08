//package gameofballpassing;

import java.util.*;
import java.io.*;

public class gameofballpassing {
	public static void main(String[] args) throws IOException {
		
		//1649B
		
		//notice that you can simulate ball passes by subtracting 1 from whichever player you want to pass the ball.
		
		//the key here is to equalize the two players with the most amount of ball passes, while keeping them at the top.
		//if you can do this, then it is guaranteed that you can simulate it using only 1 ball. 
		
		//notice that if you can equalize the top 2, then you can pass the ball among them until you have equalized the 
		//top 3, and then equalize the top 4 and so on. Only having 1 top passer doesn't work since a person can't
		//pass the ball to themselves
		
		//the only case which you can't equalize the top 2 is when the top player has more passes than all the
		//other players combined. In this case, the solution is to use 1 ball to remove as many passes as possible
		//from the top player by always passing with him. Once everybody else has run out of passes, each of the remaining
		//passes that the top player has is an extra ball. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			long sum = 0;
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long[] nums = new long[n];
			long max = 0;
			for(int i = 0; i < n; i++) {
				nums[i] = Long.parseLong(st.nextToken());
				sum += nums[i];
				max = Math.max(nums[i], max);
			}
			long target = sum / 2;
			if(max > target) {
				fout.append(max - (sum - max)).append("\n");
			}
			else if(sum == 0) {
				fout.append("0\n");
			}
			else {
				fout.append("1\n");
			}
		}
		System.out.print(fout);
	}
}	
