//package checkpoints;

import java.util.*;
import java.io.*;

public class checkpoints {
	public static void main(String[] args) throws IOException {
		
		//1453D
		
		//notice that when you put down a checkpoint, anything that comes before doesn't matter anymore.
		
		//1 checkpoint stage: 2 attempts. 1 checkpoint stage, 1 not checkpoint: 6 attempts. 1 checkpoint stage, n not checkpoint: (1 checkpoint stage, n - 1 not checkpoint) * 2 + 2;
		
		//greedily add the maximum amount each time.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			long k = Long.parseLong(fin.readLine());
			if(k % 2 == 1) {
				fout.append("-1\n");
			}
			else {
				long pointer = 2;
				long cost = 1;
				long sum = 0;
				StringBuilder ans = new StringBuilder();
				while(k != 0) {
					while(pointer > k) {
						pointer -= 2;
						pointer /= 2;
						cost --;
					}
					while((pointer * 2) + 2 <= k) {
						pointer *= 2;
						pointer += 2;
						cost ++;
					}
					k -= pointer;
					sum += cost;
					ans.append("1 ");
					for(int i = 0; i < cost - 1; i++) {
						ans.append("0 ");
					}
				}
				if(sum > 2000) {
					fout.append("-1\n");
				}
				else {
					fout.append(sum).append("\n").append(ans).append("\n");
				}
			}
		}
		System.out.print(fout);
	}
}
