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

        if (Input.GetKey(KeyCode.A))
        {
            if (aFloat < 1)
            {
                aFloat += 0.01f;
            }
        }

        if (Input.GetKey(KeyCode.R))
        {
            if (rFloat < 1)
            {
                rFloat += 0.01f;
            }
        }

        if (Input.GetKey(KeyCode.G))
        {
            if (gFloat < 1)
            {
                gFloat += 0.01f;
            }
        }

        if (Input.GetKey(KeyCode.B))
        {
            if (bFloat < 1)
            {
                bFloat += 0.01f;
            }
        }
        myColor = new Color(xPos, yPos, bFloat, aFloat);
        myRenderer.material.color = myColor;
    }
}
