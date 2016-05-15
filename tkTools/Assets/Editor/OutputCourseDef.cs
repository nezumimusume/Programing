using UnityEngine;
using System.Collections;
using UnityEditor;
using System.IO;
using System.Text;

public class OutputCourseDef : MonoBehaviour {

    [MenuItem("Window/コース定義 出力")]
    public static void ShowWindow()
    {
		GameObject cource = GameObject.Find("Cource");
        Transform[] courcePoint = cource.GetComponentsInChildren<Transform>();
        string headerTxt = "";
        foreach (Transform tr in courcePoint)
        {
            if (tr.gameObject == cource)
            {
                continue;
            }
            headerTxt += string.Format("D3DXVECTOR3({0}f, {1}f, {2}f), //{3}\n", tr.position.x, tr.position.y, tr.position.z, tr.name);
        }

        StreamWriter sw = new StreamWriter("Cource.h", false, Encoding.UTF8);
        sw.Write(headerTxt);
        sw.Close();
    }

}
