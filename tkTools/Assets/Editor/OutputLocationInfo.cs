using UnityEngine;
using System.Collections;
using UnityEditor;
using System.IO;
using System.Text;

public class OutputLocationInfo : MonoBehaviour {
    /// <summary>
    /// 名前から不要な文字をトリム
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    static string TrimModelName(string name)
    {
        string modelName = name.Split('(')[0];
        char[] trim = { ' ', '.' };
        while (true)
        {
            string trimString = modelName.TrimEnd(trim);
            if (trimString == modelName)
            {
                //トリムできた。
                break;
            }
            modelName = trimString;
        }
        return modelName;
    }
    [MenuItem("Window/配置情報 出力")]
    public static void ShowWindow()
    {
        GameObject location = GameObject.Find("Location");
        Transform[] locs = location.GetComponentsInChildren<Transform>();
        string outputTxt = "";
        //マップチップを出力。
        foreach (Transform tr in locs)
        {
            if (!tr.GetComponent<MapChip>())
            {
                //マップチップが取得できないオブジェクトは無視。
                continue;
            }
            string modelName = TrimModelName(tr.name);
            outputTxt += string.Format("//{0}\n", modelName);
            outputTxt += "{\n";
            outputTxt += string.Format("\t\"{0}\",\n", modelName);
            outputTxt += string.Format("\tCVector3({0:f}f, {1:f}f, {2:f}f),             //平行移動\n", tr.localPosition.x, tr.localPosition.y, tr.localPosition.z);
            outputTxt += string.Format("\tCQuaternion({0:f}f, {1:f}f, {2:f}f, {3:f}f ),  //回転\n", tr.localRotation.x, tr.localRotation.y, tr.localRotation.z, tr.localRotation.w);
            outputTxt += "},\n";
        }
        StreamWriter sw = new StreamWriter(@"C:\GitHub\Programing\UnityChanDemo\SkinAnimationDemo\locationInfo.h", false, Encoding.UTF8);
        sw.Write(outputTxt);
        sw.Close();

        outputTxt = "";
        //エネミーを出力。
        foreach (Transform tr in locs)
        {
            Enemy e = tr.GetComponent<Enemy>();
            if (e == null)
            {
                //Enemyが取得できないオブジェクトは無視。
                continue;
            }
            string modelName = TrimModelName(tr.name);
            outputTxt += string.Format("//{0}\n", modelName);
            outputTxt += "{\n";
            outputTxt += string.Format("\t\"{0}\",\n", modelName);
            outputTxt += string.Format("\tCVector3({0:f}f, {1:f}f, {2:f}f),             //平行移動\n", tr.localPosition.x, tr.localPosition.y, tr.localPosition.z);
            outputTxt += string.Format("\tCQuaternion({0:f}f, {1:f}f, {2:f}f, {3:f}f ),  //回転\n", tr.localRotation.x, tr.localRotation.y, tr.localRotation.z, tr.localRotation.w);
            outputTxt += "},\n";
        }
        sw = new StreamWriter(@"C:\GitHub\Programing\UnityChanDemo\SkinAnimationDemo\Enemy\EnemyInfo.h", false, Encoding.UTF8);
        sw.Write(outputTxt);
        sw.Close();

    }

    void OnGUI()
    {

    }
}
