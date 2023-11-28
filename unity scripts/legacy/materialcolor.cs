using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class materialcolor : MonoBehaviour
{
    public Renderer myRenderer;
    public Color myColor;
    public float rFloat;
    public float gFloat;
    public float bFloat;
    public float aFloat;
    public float xPos;
    public float yPos;
    public GameObject cube;
    public Material material1;
    public Material material2;
    public Material material3;
    public Material material4;
    public Material material5;
    // Start is called before the first frame update
    void Start()
    {
        aFloat = 1;
        myRenderer = gameObject.GetComponent<Renderer>();
    }

    // Update is called once per frame
    void Update()
    {
        xPos = cube.transform.position.x;
        yPos = cube.transform.position.y;

        if (xPos<0.2 && xPos>0)
        {
            myRenderer.material = material1;
        }

        if (xPos < 0.4 && xPos > 0.2)
        {
            myRenderer.material = material2;
        }

        if (xPos < 0.6 && xPos > 0.4)
        {
            myRenderer.material = material3;
        }

        if (xPos < 0.8 && xPos > 0.6)
        {
            myRenderer.material = material4;
        }

        if (xPos < 1 && xPos > 0.8)
        {
            myRenderer.material = material5;
        }

    }
}
