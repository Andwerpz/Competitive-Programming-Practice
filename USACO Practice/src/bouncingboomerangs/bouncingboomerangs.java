//package bouncingboomerangs;

import java.util.*;
import java.io.*;

public class bouncingboomerangs {
	public static void main(String[] args) throws IOException {
		
		//1428D
		
		//quite the challenging implementation problem. There are several observations:
		
		//it is best to start from either the top or bottom row and work your way to the other side.
		
		//you can "chain" 3s. 
		
		//every chain has to end with a 1. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] nums = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int numObstacle = 0;
		ArrayList<ArrayDeque<Integer>> dict = new ArrayList<ArrayDeque<Integer>>();
		for(int i = 0; i < 4; i++) {
			dict.add(new ArrayDeque<Integer>());
		}
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			dict.get(nums[i]).add(i + 1);
		}
		StringBuilder fout = new StringBuilder();
		boolean isValid = true;
		int row = 1;
		while(dict.get(1).size() != 0) {
			int nextOne = dict.get(1).poll();
			if(dict.get(2).peek() != null && dict.get(3).peek() != null && dict.get(2).peek() < nextOne && dict.get(3).peek() < nextOne && dict.get(2).peek() > dict.get(3).peek()) {
				int nextTwo = dict.get(2).poll();
				int nextThree = dict.get(3).poll();
				fout.append(row).append(" ").append(nextThree).append("\n");
				numObstacle ++;
				while(dict.get(3).peek() != null && dict.get(3).peek() < nextTwo) {
					nextThree = dict.get(3).poll();
					fout.append(row).append(" ").append(nextThree).append("\n");
					fout.append(row + 1).append(" ").append(nextThree).append("\n");
					row ++;
					numObstacle += 2;
				}
				//System.out.println(nextOne + " " + nextTwo + " " + nextThree);
				fout.append(row + 1).append(" ").append(nextOne).append("\n");
				fout.append(row).append(" ").append(nextTwo).append("\n");
				fout.append(row + 1).append(" ").append(nextTwo).append("\n");
				numObstacle += 3;
				row += 2;
			}
			else if(dict.get(2).peek() != null && dict.get(2).peek() < nextOne) {
				int nextTwo = dict.get(2).poll();
				fout.append(row).append(" ").append(nextOne).append("\n");
				fout.append(row).append(" ").append(nextTwo).append("\n");
				numObstacle += 2;
				row ++;
			}
			else if(dict.get(3).peek() != null && dict.get(3).peek() < nextOne) {
				int nextThree = dict.get(3).poll();
				fout.append(row).append(" ").append(nextThree).append("\n");
				numObstacle ++;
				while(dict.get(3).peek() != null && dict.get(3).peek() < nextOne) {
					nextThree = dict.get(3).poll();
					fout.append(row).append(" ").append(nextThree).append("\n");
					fout.append(row + 1).append(" ").append(nextThree).append("\n");
					row ++;
					numObstacle += 2;
				}
				fout.append(row).append(" ").append(nextOne).append("\n");
				fout.append(row + 1).append(" ").append(nextOne).append("\n");
				numObstacle += 2;
				row += 2;
			}
			else {
				fout.append(row).append(" ").append(nextOne).append("\n");
				numObstacle ++;
				row ++;
			}
			if(row < -1) {
				isValid = false;
				break;
			}
		}
		if(dict.get(2).size() != 0 || dict.get(3).size() != 0) {
			isValid = false;
		}
		if(isValid) {
			System.out.print(numObstacle + "\n" + fout);
		}
		else {
			System.out.println("-1\n");
		}
	}
}
