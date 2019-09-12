/*
	max(min) queue with O(1) get_max(min).
	 
	Tips:
		- Useful for sliding window 1D and 2D. 
		- For 2D problems, you will need to pre-compute another matrix, 
		by making a row-wise traversal, and calculating the min/max value 
		beginning in each cell. Then you just make a column-wise traverse 
		as they were each an independent array.
*/

struct max_queue
{
	queue<ll> q;
	deque<ll> s;
	
	int size()
	{
		return (int)q.size();
	}
	
	void push(ll val)
	{
		// while (!s.empty() && s.back() > val) -> for a min_queue
		while (!s.empty() && s.back() < val) // for a max_queue
			s.pop_back();
		s.push_back(val);
		
		q.push(val);
	}
	
	void pop()
	{
		ll u = q.front();
		q.pop();
		
		if (!s.empty() && s.front() == u)
			s.pop_front();
	}
	
	ll get_max()
	{
		return s.front(); // same for min and max queue
	}
	
};
