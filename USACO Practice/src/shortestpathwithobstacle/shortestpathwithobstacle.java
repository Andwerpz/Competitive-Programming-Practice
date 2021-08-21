//package shortestpathwithobstacle;

import java.util.*;
import java.io.*;

public class shortestpathwithobstacle {
	public static void main(String[] args) throws IOException {
		
		//1547A
		
		//notice there is only 1 obstacle. This means that if the two points don't share the x and y coordinate, then the obstacle is irrelevant, since there are 
		//two shortest paths between the two points. The only case where it is relevant is where the two points share an x or y coordinate, essentially making it so that there is only 
		//1 shortest path. In that case, just add 2 to the shortest path, and that's the answer.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			fin.readLine();
			int[][] nums = new int[3][2];
			for(int i = 0; i < 3; i++) {
				
				StringTokenizer st = new StringTokenizer(fin.readLine());
				nums[i][0] = Integer.parseInt(st.nextToken());
				nums[i][1] = Integer.parseInt(st.nextToken());
			}
			if(nums[0][0] == nums[1][0] && nums[1][0] == nums[2][0] && Math.min(nums[0][1], nums[1][1]) < nums[2][1] && Math.max(nums[0][1], nums[1][1]) > nums[2][1]) {
				fout.append(Math.abs(nums[0][1] - nums[1][1]) + 2);
			}
			else if(nums[0][1] == nums[1][1] && nums[1][1] == nums[2][1] && Math.min(nums[0][0], nums[1][0]) < nums[2][0] && Math.max(nums[0][0], nums[1][0]) > nums[2][0]) {
				fout.append(Math.abs(nums[0][0] - nums[1][0]) + 2);
			}
			else {
				fout.append(Math.abs(nums[0][0] - nums[1][0]) + Math.abs(nums[0][1] - nums[1][1]));
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
