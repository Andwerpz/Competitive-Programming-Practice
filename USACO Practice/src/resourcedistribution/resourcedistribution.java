//package resourcedistribution;

import java.util.*;
import java.io.*;

public class resourcedistribution {
	
	static int[] nums;
	
	public static int search(int val) {	//gets the first number greater than or equal to val
		int low = 0;
		int high = nums.length - 1;
		int mid = low + (high - low) / 2;
		int ans = high;
		while(low <= high) {
			if(nums[mid] >= val) {
				if(ans > mid) {
					ans = mid;
				}
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
			mid = low + (high - low) / 2;
		}
		return ans;
	}
	
	public static StringBuilder solve(int x1, int x2, int[][] order) {
		int n = nums.length;
		int k2 = -1;
		int k1 = 0;
		int p1 = 0;
		for(int i = 0; i < n; i++) {
			int sum = nums[i] * (n - i);
			if(sum >= x2 && n - i < k2 || k2 == -1) {
				k2 = n - i;
			}
		}
		boolean isValid = false;
		int startLoc = 0;
		//System.out.println(k2);
		for(int i = 1; i < n - (k2 == -1? n : k2) + 1; i++) {
			//System.out.println(i);
			k1 = i;
			p1 = x1 / k1 + (x1 % k1 == 0? 0 : 1);
			startLoc = search(p1);
			if(startLoc + k1 - 1 < n - k2) {
				isValid = true;
				break;
			}
		}
		StringBuilder fout = new StringBuilder();
		if(isValid) {
			fout.append("Yes\n");
			fout.append(k1 + " " + k2 + "\n");
			for(int i = startLoc; i < startLoc + k1; i++) {
				fout.append(order[i][1] + " ");
			}
			fout.append("\n");
			for(int i = n - k2; i < n; i++) {
				fout.append(order[i][1] + " ");
			}
		}
		else {
			fout.append("No");
		}
		return fout;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int x1 = Integer.parseInt(st.nextToken());
		int x2 = Integer.parseInt(st.nextToken());
		nums = new int[n];
		int[][] order = new int[n][2];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			order[i][0] = nums[i];
			order[i][1] = i + 1;
		}
		Arrays.sort(nums);
		Arrays.sort(order, (a, b) -> a[0] - b[0]);
		String ans = solve(x1, x2, order).toString();
		if(ans.equals("No")) {
			ans = solve(x2, x1, order).toString();
			if(!ans.equals("No")) {
				fin = new BufferedReader(new StringReader(ans));
				StringBuilder temp = new StringBuilder();
				temp.append(fin.readLine() + "\n");
				st = new StringTokenizer(fin.readLine());
				String a = st.nextToken();
				String b = st.nextToken();
				//System.out.println(b + " " +a );
				temp.append(b + " " + a + "\n");
				a = fin.readLine();
				b = fin.readLine();
				temp.append(b + "\n" + a);
				ans = temp.toString();
			}
		}
		
		System.out.println(ans);
	}
}
