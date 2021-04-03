
package rookbishopandking;

import java.util.*;
import java.io.*;

public class rookbishopandking {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		
		int[] start = new int[] {Integer.parseInt(st.nextToken()) - 1, Integer.parseInt(st.nextToken()) - 1};
		int[] end = new int[] {Integer.parseInt(st.nextToken()) - 1, Integer.parseInt(st.nextToken()) - 1};
		
		if(start[0] == end[0] && start[1] != end[1]) {
			
		}
		else if(start[1] == end[1] && start[0] != end[0]) {
			
		}
		else if(start[0] != end[0] && start[1] != end[1]) {
			
		}
		
	}
}
