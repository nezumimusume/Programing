﻿// Fantasy Skybox
// Version: 1.2.6
// Unity 4.7.1 or higher and Unity 5.3.4 or higher compatilble, see more info in Readme.txt file.
//
// Author:				Gold Experience Team (http://www.ge-team.com)
//
// Unity Asset Store:	https://www.assetstore.unity3d.com/en/#!/content/18216
// GE Store:			http://www.ge-team.com/store/en/products/fantasy-skybox/
//
// Please direct any bugs/comments/suggestions to support e-mail (geteamdev@gmail.com).

#region Namespaces

using UnityEngine;
using System.Collections;
using UnityEngine.UI;

#endregion // Namespaces

// ######################################################################
//
// GE_FantasySkybox_UIs handles user key inputs.
//
// Note this class is attached with GE_FantasySkybox_UIs object in "Fantasy Skybox Demo (960x600px)" scene.
//
// ######################################################################

public class GE_FantasySkybox_UIs : MonoBehaviour
{
	// ########################################
	// Variables
	// ########################################

	#region Variables

	// Canvas
	public Canvas m_Canvas = null;

	// Help
	public Button m_Help_Button = null;
	public GameObject m_Help_Window = null;

	// Details
	public GameObject m_Details = null;

	// Details Panel
	public GameObject m_PanelDetails = null;

	// HowTo
	public GameObject m_HowTo = null;

	#endregion // Variables

	// ########################################
	// MonoBehaviour Functions
	// http://docs.unity3d.com/ScriptReference/MonoBehaviour.html
	// ########################################

	#region MonoBehaviour

	// Awake is called when the script instance is being loaded.
	// http://docs.unity3d.com/ScriptReference/MonoBehaviour.Awake.html
	void Awake()
	{
		// Set GUIAnimSystemFREE.Instance.m_AutoAnimation to false, 
		// this will let you control all GUI Animator elements in the scene via scripts.
		if (enabled)
		{
			GUIAnimSystemFREE.Instance.m_GUISpeed = 1.0f;
			GUIAnimSystemFREE.Instance.m_AutoAnimation = false;
		}
	}

	// Start is called on the frame when a script is enabled just before any of the Update methods is called the first time.
	// http://docs.unity3d.com/ScriptReference/MonoBehaviour.Start.html
	void Start()
	{
		// Play UI move-in animations
		StartCoroutine(ShowUIs());
	}

	// Update is called every frame, if the MonoBehaviour is enabled.
	// http://docs.unity3d.com/ScriptReference/MonoBehaviour.Update.html
	void Update()
	{
	}

	#endregion // MonoBehaviour

	// ########################################
	// Play UI move-in functions
	// ########################################

	#region Play UI move-in functions

	// Play UI move-in animations
	IEnumerator ShowUIs()
	{
		// Disable all buttons of m_Canvas
		// http://docs.unity3d.com/Manual/script-GraphicRaycaster.html
		GUIAnimSystemFREE.Instance.SetGraphicRaycasterEnable(m_Canvas, false);

		yield return new WaitForSeconds(0.5f);

		// Play m_Help_Button's move-in animation
		GUIAnimSystemFREE.Instance.MoveIn(m_Help_Button.transform, true);

		yield return new WaitForSeconds(0.25f);

		// Play m_Details's move-in animation
		GUIAnimSystemFREE.Instance.MoveIn(m_Details.transform, true);

		// Play m_PanelDetails's move-in animation
		GUIAnimSystemFREE.Instance.MoveIn(m_PanelDetails.transform, true);

		// Play m_HowTo's move-in animation
		GUIAnimSystemFREE.Instance.MoveIn(m_HowTo.transform, true);

		// Enable all buttons of m_Canvas
		// http://docs.unity3d.com/Manual/script-GraphicRaycaster.html
		GUIAnimSystemFREE.Instance.SetGraphicRaycasterEnable(m_Canvas, true);
	}

	#endregion // Play UI move-in functions

	// ########################################
	// UI Respond functions
	// ########################################

	#region UI Respond functions

	// User press Help button
	public void Button_Help()
	{
		// Play m_Help_Button's move-in animation
		GUIAnimSystemFREE.Instance.MoveOut(m_Help_Button.transform, true);

		// Play m_Help_Window's move-in animation
		GUIAnimSystemFREE.Instance.MoveIn(m_Help_Window.transform, true);
	}

	// User press Minimize button
	public void Button_Help_Minimize()
	{
		// Play m_Help_Button's move-in animation
		GUIAnimSystemFREE.Instance.MoveIn(m_Help_Button.transform, true);

		// Play m_Help_Window's move-in animation
		GUIAnimSystemFREE.Instance.MoveOut(m_Help_Window.transform, true);
	}

	// User press Support button
	public void Button_Help_Support()
	{
		// http://docs.unity3d.com/ScriptReference/Application.OpenURL.html
		Application.OpenURL("mailto:geteamdev@gmail.com");
	}

	// User press Products button
	public void Button_Help_Products()
	{
		// http://docs.unity3d.com/ScriptReference/Application.ExternalEval.html
		//Application.ExternalEval("window.open('http://www.ge-team.com/store/en/products/','GOLD EXPERIENCE TEAM')");

        // http://docs.unity3d.com/ScriptReference/Application.OpenURL.html
        Application.OpenURL("http://www.ge-team.com/store/en/products/");
	}

	#endregion // UI Respond Functions
}
