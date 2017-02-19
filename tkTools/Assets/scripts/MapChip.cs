using UnityEngine;
using System.Collections;

public class MapChip : MonoBehaviour {
    public Quaternion invRot { get; set; }
	// Use this for initialization
    void Awake()
    {
        invRot = Quaternion.identity;
    }
	void Start () {
	    
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
