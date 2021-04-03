import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class flightroutescheckver2 {
	static ArrayList<Integer>[] adj, invadj;
	static void inversedfs(int node){
		for (int a : invadj[node]) {
			if (!vis[a]) {
				vis[a] = true;
				inversedfs(a);
			}
		}
	}
	static boolean[] vis;
	static void dfs(int node){
		for (int a : adj[node]) {
			if (!vis[a]) {
				vis[a] = true;
				dfs(a);
			}
		}
	}

	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(st.nextToken()), m = Integer.parseInt(st.nextToken());
		adj = new ArrayList[n];
		vis = new boolean[n];
		for (int i = 0; i < n; i++) {
			adj[i] = new ArrayList<Integer>();
		}
		invadj = new ArrayList[n];
		for (int i = 0; i < n; i++) {
			invadj[i] = new ArrayList<Integer>();
		}
		for (int i = 0; i < m; i++) {
			st = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(st.nextToken())-1, b=Integer.parseInt(st.nextToken())-1;
			adj[a].add(b);
			invadj[b].add(a);
		}
		//run a dfs from node 1
		vis[0] = true;
		dfs(0);
		for (int i = 0; i < n; i++) {
			if (!vis[i]) {
				System.out.println("NO");
				i++;
				System.out.print(1 + " " + i);
				System.exit(0);
			}
		}
		vis = new boolean[n];
		vis[0] = true;
		inversedfs(0);
		for (int i = 0; i < n; i++) {
			if (!vis[i]) {
				System.out.println("NO");
				i++;
				System.out.print(i + " " + 1);
				System.exit(0);
			}
		}
		System.out.println("YES");
	}
}