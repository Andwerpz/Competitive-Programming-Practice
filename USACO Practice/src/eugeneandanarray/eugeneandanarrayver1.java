package eugeneandanarray;

import java.util.*;
import java.io.*;

public class eugeneandanarrayver1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		long[] nums = new long[n];
		long[] pfx = new long[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			pfx[i] = nums[i] + (i == 0? 0 : pfx[i - 1]);
		}
		HashSet<Long> dict = new HashSet<Long>();
		dict.add(0l);
		long ans = 0;
		long offset = 0;
		int pointer = 0;
		for(int i = 0; i < n; i++) {
			while(pointer != n && !dict.contains(pfx[pointer])) {
				dict.add(pfx[pointer]);
				pointer ++;
			}
			if(nums[i] != 0) {
				System.out.println("ADD");
				ans += pointer - i;
			}
			dict.remove(pfx[i]);
			pointer = Math.max(pointer, i);
			System.out.println(i + " " + pointer);
		}
		if(nums[n - 1] != 0) {
			System.out.println("ADD");
			ans += pointer - n - 1;
		}
		System.out.println(ans);
	}
}
