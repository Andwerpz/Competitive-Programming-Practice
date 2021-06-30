//package stonegame;

import java.util.*;
import java.io.*;

public class stonegame {
	
	public static int removeLarge(ArrayList<Integer> arr) {
		int n = arr.size();
		int max = 0;
		int maxLoc = 0;
		for(int i = 0; i < arr.size(); i++) {
			if(arr.get(i) > max) {
				max = arr.get(i);
				maxLoc = i;
			}
		}
		int ans = 0;
		if(maxLoc < (n / 2) && n % 2 == 0 || maxLoc <= (n / 2) && n % 2 == 1) {
			while(arr.get(0) != max) {
				ans ++;
				arr.remove(0);
			}
			ans ++;
			arr.remove(0);
		}
		else {
			while(arr.get(arr.size() - 1) != max) {
				arr.remove(arr.get(arr.size() - 1));
				ans ++;
			}
			arr.remove(arr.get(arr.size() - 1));
			ans ++;
		}
		return ans;
	}
	
	public static int removeSmall(ArrayList<Integer> arr) {
		int n = arr.size();
		int min = Integer.MAX_VALUE;
		int minLoc = 0;
		for(int i = 0; i < arr.size(); i++) {
			if(arr.get(i) < min) {
				min = arr.get(i);
				minLoc = i;
			}
		}
		int ans = 0;
		if(minLoc < (n / 2) && n % 2 == 0 || minLoc <= (n / 2) && n % 2 == 1) {
			while(arr.get(0) != min) {
				ans ++;
				arr.remove(0);
			}
			ans ++;
			arr.remove(0);
		}
		else {
			while(arr.get(arr.size() - 1) != min) {
				arr.remove(arr.get(arr.size() - 1));
				ans ++;
			}
			arr.remove(arr.get(arr.size() - 1));
			ans ++;
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1538A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			int min = Integer.MAX_VALUE;
			int minLoc = 0;
			int max = 0;
			int maxLoc = 0;
			ArrayList<Integer> t1 = new ArrayList<Integer>();
			ArrayList<Integer> t2 = new ArrayList<Integer>();
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				t1.add(next);
				t2.add(next);
			}
			int ans1 = 0;
			int ans2 = 0;
			ans1 += removeLarge(t1);
			ans1 += removeSmall(t1);
			ans2 += removeSmall(t2);
			ans2 += removeLarge(t2);
			fout.append(Math.min(ans1, ans2)).append("\n");
		}
		System.out.print(fout);
	}
}
