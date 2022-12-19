using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Valve.VR;

public class materialcolor : MonoBehaviour
{
    public Renderer myRenderer;
    public Color myColor;
    public float rFloat;
    public float gFloat;
    public float bFloat;
    public float aFloat;
    public float xPos;
    private float xStart;
    public float treshold;
    private float zStart;
    public float zPos;
    public GameObject cube;
    public GameObject headset;
    public Material materialnumber;
    public Material material2;
    public Material material3;
    public Material material4;
    public Material material5;
    public Material material6;
    public Material material7;
    public Material material8;
    public Material material9;
    public Material[] materials;
    public int[] xpositie = new int [20]; // dit is onze matrix die we zullen gebruiken om de juiste foto te laden
    public int[] zpositie = new int[20]; // dit is onze matrix die we zullen gebruiken om de juiste foto te laden
    int materialcounter;
    float xMax = 2.5f;
    float zMax = -1.5f;
    float remappedx;
    float remappedz;
    public string fotonaam;
    float headDistanceCheckz;
    

    // Start is called before the first frame update
    void Start()
    {
        aFloat = 1;
        myRenderer = gameObject.GetComponent<Renderer>();
        //headDistanceCheckx = cube.transform.position.x;
        xStart = headset.transform.position.x;
        zStart = headset.transform.position.z;
        Debug.Log(xStart);
        Debug.Log(zStart);
    }

    // Update is called once per frame
    void Update()
    {
        cube.transform.position = headset.transform.position;
        xPos = cube.transform.position.x;
        zPos = cube.transform.position.z;

        /*if(Input.GetKeyDown("space"))
            {
                Debug.Log("spaced out");
                Valve.VR.OpenVR.Chaperone.ResetZeroPose(ETrackingUniverseOrigin.TrackingUniverseSeated); 
            }*/

        if (Mathf.Abs(xPos - xStart) > treshold)
        {
            Debug.Log("triggersysteem om niewe foto in the laden"); //
            xStart = xPos;
            pictureretriever(xPos, zPos);//hiermee haal je een foto op
            myRenderer.material.mainTexture = Resources.Load<Texture2D>(fotonaam);
        }

        /*
         * werkende demo in 2 richtingen, nu met counter hieronder verder werken
       
        
        if (xPos < 1.36 && xPos > 1.33)
        {
            if (zPos < -0.57 && zPos > -0.6)
            { myRenderer.material = material3; Debug.Log("image3"); }

            if (zPos < -0.6 && zPos > -0.63)
            { myRenderer.material = material4; Debug.Log("image4"); }
        }
        

       
        if (xPos > (headDistanceCheckx + 0.03))
        {
            xpicNumber++;
            Debug.Log("xpicNumber="+xpicNumber);
            headDistanceCheckx = (float)(headDistanceCheckx + 0.03);
            materialnumber = materials[materialcounter];
            myRenderer.material = materialnumber;
        }
        else if(xPos < (headDistanceCheckx - 0.03))
        {
            xpicNumber--;
            Debug.Log("xpicNumber=" + xpicNumber);
            headDistanceCheckx = (float)(headDistanceCheckx - 0.03);
            myRenderer.material = material2;
        }

        if (zPos > (headDistanceCheckz + 0.03))
        {
            zpicNumber++;
            Debug.Log("zpicNumber=" + zpicNumber);
            headDistanceCheckz = (float)(headDistanceCheckz + 0.03);
            materialnumber = materials[materialcounter];
            myRenderer.material = materialnumber;
        }
        else if (zPos < (headDistanceCheckz - 0.03))
        {
            zpicNumber--;
            Debug.Log("zpicNumber=" + zpicNumber);
            headDistanceCheckz = (float)(headDistanceCheckz - 0.03);
            myRenderer.material = material2;
        }
        */
        //Debug.Log("xPos =" + xPos);
        //Debug.Log("zPos =" + zPos);
        //Debug.Log("xStart =" + xStart);
        //Debug.Log("delta ="+Mathf.Abs(xPos - xStart));
        
        //Debug.Log("zStart =" + zStart);
    }
    void pictureretriever(float x, float z)
    {
        remappedx = (int)((x + (xMax / 2))/treshold);
        remappedz = (int)((z + (zMax / 2)) / treshold);
        fotonaam = (remappedx+"-"+remappedz);
        Debug.Log(fotonaam);

    }
}
