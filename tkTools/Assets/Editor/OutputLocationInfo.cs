using UnityEngine;
using System.Collections;
using UnityEditor;
using System.IO;
using System.Text;

public class OutputLocationInfo : MonoBehaviour {

    [MenuItem("Window/配置情報 出力")]
    public static void ShowWindow()
    {
        GameObject collision = GameObject.Find("Location");
        Transform[] collisions = collision.GetComponentsInChildren<Transform>();
        string headerTxt = "";
        foreach (Transform tr in collisions)
        {
            if (tr.gameObject == collision)
            {
                continue;
            }
            string modelName = tr.name.Split('(')[0];
            char[] trim = { ' ', '.' };
            while (true)
            {
                string trimString = modelName.TrimEnd(trim);
                if(trimString == modelName)
                {
                    //トリムできた。
                    break;
                }
                modelName = trimString;
            }
            headerTxt += string.Format("//{0}\n", modelName);
            headerTxt += "{\n";
            headerTxt += string.Format("\t\"{0}\",\n", modelName);                       
            headerTxt += string.Format("\tCVector3({0:f}f, {1:f}f, {2:f}f),             //平行移動\n", tr.localPosition.x, tr.localPosition.y, tr.localPosition.z);
            headerTxt += string.Format("\tCQuaternion({0:f}f, {1:f}f, {2:f}f, {3:f}f ),  //回転\n", tr.localRotation.x, tr.localRotation.y, tr.localRotation.z, tr.localRotation.w);
            headerTxt += "},\n";
        }

        StreamWriter sw = new StreamWriter(@"C:\GitHub\Programing\UnityChanDemo\SkinAnimationDemo\locationInfo.h", false, Encoding.UTF8);
        sw.Write(headerTxt);
        sw.Close();
    }

    void OnGUI()
    {

    }
}
