class PriorityQueueElement
{
  public:
	bool operator<(QueueElement arg) { return (priority < arg.priority); };
  private:
	int priority;
};

class GraphicsObject : QueueElement
{
	// Everything else defined here
};

class PriorityQueue
{
  public:
	add(PriorityObject &arg); // Adds in order
	PriorityObject &extract(); // Extracts highest priority element
  private:
	PriorityObject *head;
};

class Graphics
{
  public:
	bool next();
	bool process(GraphicsObject arg);
	//Other stuff goes here
  private:
	PriorityQueue queue;
	//Other stuff goes here
};

bool Graphics::next()
{
	QueueElement tmp = queue.extract();
	
	if ( dynamic_cast<GraphicsObject>(tmp) )
		return process(tmp);

}
