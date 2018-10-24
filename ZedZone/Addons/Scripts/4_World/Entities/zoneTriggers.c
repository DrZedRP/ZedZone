class ZoneTriggerInsider
{
	ref OLinkT insider;
	int timeStamp;
	vector position;
	void ZoneTriggerInsider(Object obj)
	{
		insider = new OLinkT(obj);
	}

	Object GetObject()
	{
		return insider.Ptr();
	}
};

class ZoneTrigger extends Trigger
{

	ref array<ref ZoneTriggerInsider> m_ZoneInsiders;
	Particle m_ParticleEfx;
	static vector m_mins;
	static vector m_maxs;
	static float m_radius;


	override void OnEnter(Object obj)
	{
		zzDebugPrint(this.ToString()+ ": " + "OnEnter = " + obj);
		float dist =  vector.Distance(obj.GetPosition(),GetPosition());
		zzDebugPrint(this.ToString()+ ": " + "OnEnter Distance = " + dist);

	}

	override void OnLeave(Object obj)
	{
		zzDebugPrint(this.ToString()+ ": " + "OnLeave = " + obj);

	}
	
	override protected void UpdateInsiders(int timeout)
	{
		int timeStamp = g_Game.GetTime();

		for(int n = 0; n < m_ZoneInsiders.Count(); )
		{
			ZoneTriggerInsider ins = m_ZoneInsiders.Get(n);
			if(ins.insider == NULL)
			{
				//object has been deleted. Remove it
				m_ZoneInsiders.Remove(n);
				continue;
			}
			
		
			float dist = 0;
			if(ins.GetObject()) {
				dist =  vector.Distance(ins.GetObject().GetPosition(),GetPosition());

			}


			if(dist > m_radius)
			{
				//object left. Remove it
				OnLeave(ins.insider.Ptr());
				m_ZoneInsiders.Remove(n);
				continue;
			}

			// original code based on timestamp but touch only fires when in motion not when idle
			/*
			int timeDiff = timeStamp - ins.timeStamp;

			if(timeDiff > timeout)
			{
				//object left. Remove it
				OnLeave(ins.insider.Ptr());
				m_ZoneInsiders.Remove(n);
				continue;
			}
			*/
			 
			n++;			
		}		
	}

	override protected void AddInsider(Object obj)
	{
		ZoneTriggerInsider ins;
		for(int n = 0; n < m_ZoneInsiders.Count(); n++)
		{
			ins = m_ZoneInsiders.Get(n);
			//already in?
			if(ins.insider.Ptr() == obj)
			{
				//just update timestamp
				ins.timeStamp = g_Game.GetTime();
				ins.position = obj.GetPosition();
				return;
			}
		}
		ins = new ZoneTriggerInsider(obj);
		ins.timeStamp = g_Game.GetTime();
		ins.position = obj.GetPosition();
		m_ZoneInsiders.Insert(ins);
		OnEnter(obj);  				
	}
	
	override void EOnFrame(IEntity other, float timeSlice)
	{
		UpdateInsiders(TIMEOUT);
	}
	
	override void EOnTouch(IEntity other, int extra)
	{
		zzDebugPrint(this.ToString()+ ": " + "EOnTouch()" );

		Object obj;
		if (Class.CastTo(obj, other))
		//			if(obj.IsMan()) AddInsider(obj);

			AddInsider(obj);
	}

	void EOnContact(IEntity other, int extra)
	{
		zzDebugPrint(this.ToString()+ ": " + "EOnContact()" );


	}



	array<ref ZoneTriggerInsider> GetInsiders()
	{
		return m_ZoneInsiders;
	}

	float GetRadius(vector min, vector max)
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
	
	override void SetExtents(vector mins, vector maxs)
	{
		m_mins = mins;
		m_maxs = maxs;
		zzDebugPrint(this.ToString()+ ": " + "mins = " + mins.ToString());
		zzDebugPrint(this.ToString()+ ": " + "maxs = " + maxs.ToString());


		m_radius = GetRadius(mins,maxs);
		zzDebugPrint(this.ToString()+ ": " + "m_radius = " + m_radius);

		SetCollisionBox(mins, maxs);

		if(1)
		{
			vector mat[4];
			GetTransform(mat);
			if(shape)
			{
				shape.Destroy();
				shape = NULL;
			}
			
			shape = Shape.Create(ShapeType.BBOX, 0x1fff7f7f, ShapeFlags.WIREFRAME, mins, maxs);
			
			if (shape) // Hackfix! Function AddDShape must return Shape! That's why this condition is probably never passed!
			{
				shape.SetMatrix(mat);
			}
		}
	}


	override void EOnInit(IEntity other, int extra)
	{
		const vector mins = "0 0 0";
		const vector maxs = "0 0 0";
		SetExtents(mins, maxs);
	}

	override void EOnExtra(IEntity other, int extra)
	{
		zzDebugPrint(this.ToString()+ ": " + "EOnExtra()" );

	}

	private void ~ZoneTrigger()
	{
		Cleanup();
	}
			
	private void ZoneTrigger()
	{
		m_ZoneInsiders = new array<ref ZoneTriggerInsider>;
		SetEventMask(EntityEvent.FRAME|EntityEvent.INIT|EntityEvent.CONTACT);
		SetFlags(EntityFlags.TRIGGER, true);
				

	}
};


	
};