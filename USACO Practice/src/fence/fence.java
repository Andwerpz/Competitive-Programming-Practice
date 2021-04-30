package fence;

import java.util.*;
import java.io.*;

public class fence {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("input.txt"));
	    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("output.txt")));
		int n = Integer.parseInt(fin.readLine());
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int a = Integer.parseInt(st.nextToken());
		int b = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(fin.readLine());
		int[] nums = new int[n];
		int sum = 0;
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			sum += nums[i];
		}
		int ans = 0;
		if(a >= sum || b >= sum) {	//only one color needed. Print 0;
			fout.println(0);
		}
		else if(a + b < sum) {	//both colors combined can't color fence. Print -1;
			fout.println(-1);
		}
		else {	//the interesting case. There are enough to color the fence, but more than one color needed.
			
		}
	}
}
