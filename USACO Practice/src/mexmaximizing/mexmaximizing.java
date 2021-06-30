//package mexmaximizing;

import java.util.*;
import java.io.*;

public class mexmaximizing {
	public static void main(String[] args) throws IOException {
		
		//1294D
		
		//notice that given any number a, you can make it so that it becomes any multiple of x plus a % x. So you just have to keep track of how many numbers you have of each a % x. 
		//what i did is kept an int array storing my numbers. I had an ans variable that when i saw that i had more than one number at the current a % x, i incremented and then decremented
		//that index position.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int q = Integer.parseInt(st.nextToken());
		int x = Integer.parseInt(st.nextToken());
		int[] quant = new int[x];
		int ans = 0;
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < q; i++) {
			int next = Integer.parseInt(fin.readLine());
			next %= x;
			quant[next] ++;
			while(quant[ans % x] != 0) {
				quant[ans % x] --;
				ans ++;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
