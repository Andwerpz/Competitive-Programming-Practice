//package visits;

import java.util.*;
import java.io.*;

public class visits {
	public static void main(String[] args) throws IOException {
		
		//2022 March USACO Silver
		
		//we can represent the situation as a graph. 
		
		//notice that since each cow has exactly 1 outgoing edge, it is guaranteed that the graph
		//will consist of a number of loops. 
		
		//the thing about loops is that within the loop, you can generate a permutation that will
		//only make 1 cow not be able to visit.
		
		//there will also be 'spokes' on the loop; cows that point towards a member of the loop, but
		//are not actually part of the loop. Notice that you can always satisfy a cow that is a member
		//of a spoke
		
		//the solution is to first generate the sum of moos for all cows. Then locate all the loops, 
		//and for each loop, subtract from the sum the minimum cow in that loop
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		long ans = 0;
		int[] c = new int[n];
		int[] nums = new int[n];
		StringTokenizer st;
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			c[i] = Integer.parseInt(st.nextToken()) - 1;
			nums[i] = Integer.parseInt(st.nextToken());
		}
		boolean[] v = new boolean[n];
		boolean[] partOfLoop = new boolean[n];
		for(int i = 0; i < n; i++) {
			if(v[i]) {
				continue;
			}
			boolean visitedLoop = false;
			Stack<Integer> s = new Stack<Integer>();
			//HashSet<Integer> 
			s.add(i);
			v[i] = true;
			while(true) {
				int cur = s.peek();
				int next = c[cur];
				s.add(next);
				if(partOfLoop[next]) {
					visitedLoop = true;
					s.pop();
					break;
				}
				if(v[next]) {
					break;
				}
				v[next] = true;
			}
			if(visitedLoop) {	//we've looked at this component before
				//System.out.println("VISITED");
				for(int j : s) {
					partOfLoop[j] = true;
					ans += (long) nums[j];
				}
				continue;
			}
			int repeat = s.peek();
			long sum = 0;
			long min = Integer.MAX_VALUE;
			//System.out.println(s);
			while(true) {
				int cur = s.pop();
				partOfLoop[cur] = true;
				min = Math.min(min, nums[cur]);
				sum += (long) nums[cur];
				if(s.peek() == repeat) {
					break;
				}
			}
			ans += sum - min;
			s.pop();	//getting rid of repeat
			while(s.size() != 0) {
				int cur = s.pop();
				ans += (long) nums[cur];
				partOfLoop[cur] = true;
			}
		}
		System.out.println(ans);
	}
}
