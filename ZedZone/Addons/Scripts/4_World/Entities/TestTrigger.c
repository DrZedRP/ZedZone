#ifdef DEVELOPER
const bool DebugTestTrigger = true;
#else
const bool DebugTestTrigger = false;
#endif

class TestTriggerInsider
{
	ref OLinkT insider;
	int timeStamp;
	vector position;
	void TestTriggerInsider(Object obj)
	{
		insider = new OLinkT(obj);
	}

	Object GetObject()
	{
		return insider.Ptr();
	}
};

class TestTrigger extends ScriptedEntity
{
	const int TIMEOUT = 1000;
	ref array<ref TestTriggerInsider> m_insiders;
	Shape shape;

	protected void Cleanup()
	{
		if(shape)
		{
			shape.Destroy();
			shape = NULL;
		}			
	}

	void OnEnter(Object obj)
	{
		zzDebugPrint(this.ToString()+ ": " + "OnEnter()");

	}

	void OnLeave(Object obj)
	{
		zzDebugPrint(this.ToString()+ ": " + "OnLeave()");

	}
	
	protected void UpdateInsiders(int timeout)
	{
		int timeStamp = g_Game.GetTime();

		for(int n = 0; n < m_insiders.Count(); )
		{
			TestTriggerInsider ins = m_insiders.Get(n);
			if(ins.insider == NULL)
			{
				//object has been deleted. Remove it
				m_insiders.Remove(n);
				continue;
			}
			
			int timeDiff = timeStamp - ins.timeStamp;
			if(ins.GetObject())
				float distance = vector.Distance(ins.position, ins.GetObject().GetPosition());
			if(timeDiff > timeout && distance > 0)
			{
				//object left. Remove it
				OnLeave(ins.insider.Ptr());
				m_insiders.Remove(n);
				continue;
			}
			 
			n++;			
		}		
	}

	protected void AddInsider(Object obj)
	{
		TestTriggerInsider ins;
		for(int n = 0; n < m_insiders.Count(); n++)
		{
			ins = m_insiders.Get(n);
			//already in?
			if(ins.insider.Ptr() == obj)
			{
				//just update timestamp
				ins.timeStamp = g_Game.GetTime();
				ins.position = ins.GetObject().GetPosition();
				return;
			}
		}
		ins = new TestTriggerInsider(obj);
		ins.timeStamp = g_Game.GetTime();
		ins.position = ins.GetObject().GetPosition();
		m_insiders.Insert(ins);
		OnEnter(obj);  				
	}
	
	override void EOnFrame(IEntity other, float timeSlice)
	{
		UpdateInsiders(TIMEOUT);
	}


	override void EOnTouch(IEntity other, int extra)
	{
		//zzDebugPrint(this.ToString()+ ": " + "EOnTouch()");

		Object obj;
		if (Class.CastTo(obj, other))
			AddInsider(obj);
	}

	private float GetRadius(vector min, vector max)
	{
		vector v;
		for(int n = 0; n < 3; n++)
		{
			float m1 = Math.AbsFloat(min[n]);
			float m2 = Math.AbsFloat(max[n]);

			if(m1 > m2)
				v[n] = m1;
			else
				v[n] = m2;			
		}
		
		return v.Length();			
	}
	
	void SetExtents(vector mins, vector maxs)
	{
		zzDebugPrint(this.ToString()+ ": " + "SetExtents() " + "mins = " + mins.ToString());
		zzDebugPrint(this.ToString()+ ": " + "SetExtents() " + "maxs = " + maxs.ToString());

		SetCollisionBox(mins, maxs);
		float radius = GetRadius(mins,maxs)/2;
		zzDebugPrint(this.ToString()+ ": " + "SetExtents() " + "radius = " + radius);




	}


	override void EOnInit(IEntity other, int extra)
	{
		/*
		const vector mins = "-10 -10 -10";
		const vector maxs = "10 10 10";
		SetExtents(mins, maxs);
		*/
	}

	private void ~TestTrigger()
	{
		Cleanup();
	}
			
	private void TestTrigger()
	{
		zzDebugPrint(this.ToString()+ ": " + "TestTrigger()");
		m_insiders = new array<ref TestTriggerInsider>;
		SetEventMask(EntityEvent.FRAME|EntityEvent.INIT|EntityEvent.TOUCH);
		SetFlags(EntityFlags.TRIGGER, false);
	}
};

class ManTestTrigger extends TestTrigger
{
	override void OnEnter(Object obj)
	{
	}

	override void EOnTouch(IEntity other, int extra)
	{
		Object obj;
		if(Class.CastTo(obj, other))
		{
			if(obj.IsMan()) AddInsider(obj);
		}
	}

	array<ref TestTriggerInsider> GetInsiders()
	{
		return m_insiders;
	}

	override void EOnInit(IEntity other, int extra)
	{
		const vector mins = "-10 -10 -10";
		const vector maxs = "10 10 10";
		SetExtents(mins, maxs);
	}
	
};