#include "stdafx.h"
#include "DetailVisualization.h"

namespace OpenGLForm{
	DetailVisualization::DetailVisualization(Form ^ parentForm,Panel ^ parentPanel, GLsizei iWidth, GLsizei iHeight,ReadCSV read_csv_ref,Preprocessing_Data preprocessing_data_ref):VisualizationPanel(parentForm,parentPanel,iWidth,iHeight,read_csv_ref,preprocessing_data_ref){
			title_string();
			//Initialize mouse handler variable
			scale_x[2] = 0.0; scale_y[2] = 0.0; scale_z[2] = 0.0;
			scale_size[2] = 0.05;
			move_x[2] = 0.0; move_y[2] = 0.0; move_z[2] = 0.0;
			scale_factor[2] = 0.6;
			//Initialize window size
			windowWidth[2] = iWidth; 
			windowHeight[2] = iHeight;	
	}
	System::Void DetailVisualization::Render(int detail_width,int detial_height){
			wglmakecur();

			windowWidth[2] = detail_width;
			windowHeight[2] = detial_height;

			glClearColor(0.0, 0.0, 0.0, 0.0);  //Set the cleared screen colour to black
			glViewport(0, 0, windowWidth[2], windowHeight[2]);   //This sets up the viewport so that the coordinates (0, 0) are at the top left of the window		
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, windowWidth[2], windowHeight[2], 0, -10, 10);

			//Back to the modelview so we can draw stuff 
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the screen and depth buffer

			glTranslatef(0.0+move_x[2],0.0+move_y[2],0.0+move_z[2]);
			glScalef(scale_factor[2]+scale_x[2],scale_factor[2]+scale_y[2],scale_factor[2]+scale_z[2]);
			vector<float> color;
			color.resize(3);

			//DrawLine(0,480,windowWidth[2]*2,480);
			//DrawLine(450,0,450,1000);
			
			
			if(!raw_data_index_2D.empty())
			{	
					//int x_position = 200;
					//int y_position = 150;
					int x_position[] = {70,70,550,550,950,950};
					int y_position[] = {100,500,100,500,100,500};
					for(int dim=0;dim<6;dim++)
					{
						DrawTitle_FTGL(dim,x_position[dim],y_position[dim]-50);
						for(int i=0;i<raw_data_index_2D.size();i++)
						{				
							RECTANGLE *rect;
							int index1 = raw_data_index_2D[i][0];
							int index2 = raw_data_index_2D[i][1];
							int count = 0;
							int month,day;
							for(int i=0;i<preprocessing_data.month_vec.size();i++)
							{
								for(int j=0;j<preprocessing_data.month_vec[i].day_vec.size();j++)
								{
									if(count==index1)
									{
										month = i;
										day = j;
										break;
									}
									count++;
								}
								if(count==index1) break;
							}

							int r=1.0,g=1.0,b=1.0;

							//DrawText_FTGL(preprocessing_data.month_vec[index1].this_year, x_position-150, y_position + 10, r, g, b);
							//DrawText_FTGL_Zero_Padding(preprocessing_data.month_vec[index1].this_month, x_position-100, y_position + 10, r, g, b);
							//DrawText_FTGL_Zero_Padding(index2+1, x_position-70, y_position + 10, r, g, b);
							float value = 0.004*abs(preprocessing_data.month_vec[month].day_vec[day].hour_vec[index2].data[dim]);
							DrawText_FTGL(preprocessing_data.month_vec[month].day_vec[day].hour_vec[index2].data[dim], x_position[dim] + value + 10, y_position[dim] + 10, 1.0, 1.0, 1.0);
						
							rect = new RECTANGLE();
							rect->h = 30.0;
							rect->w = value;
							rect->x = x_position[dim];
							rect->y = y_position[dim];
							color[0] = preprocessing_data.raw_data_3D_array[index1].at<float>(index2,0);
							color[1] = preprocessing_data.raw_data_3D_array[index1].at<float>(index2,1);
							color[2] = preprocessing_data.raw_data_3D_array[index1].at<float>(index2,2);

							DrawRectWithOpenGL(rect,color);
							delete(rect);

							y_position[dim]+=35;
						}					
					}
					/*
					//x_position = 750;
					//y_position = 150;
					for(int i=0;i<raw_data_index_2D.size();i++)
					{				
						RECTANGLE *rect;
						int index1 = raw_data_index_2D[i][0];
						int index2 = raw_data_index_2D[i][1];
						int count = 0;
						int month,day;
						for(int i=0;i<preprocessing_data.month_vec.size();i++)
						{
							for(int j=0;j<preprocessing_data.month_vec[i].day_vec.size();j++)
							{
								if(count==index1)
								{
									month = i;
									day = j;
									break;
								}
								count++;
							}
							if(count==index1) break;
						}
						//DrawText_FTGL(preprocessing_data.month_vec[index1].this_year, x_position-150, y_position + 10, r, g, b);
						//DrawText_FTGL(preprocessing_data.month_vec[index1].this_month, x_position-100, y_position + 10, r, g, b);
						//DrawText_FTGL(index2+1, x_position-70, y_position + 10, r, g, b);
						float value = 0.001*abs(preprocessing_data.month_vec[month].day_vec[day].hour_vec[index2].data[1]);
						DrawText_FTGL(preprocessing_data.month_vec[month].day_vec[day].hour_vec[index2].data[1], x_position[1] + value + 10, y_position[1] + 10, 1.0, 1.0, 1.0);
						
						rect = new RECTANGLE();
						rect->h = 30.0;
						rect->w = value;
						rect->x = x_position[1];
						rect->y = y_position[1];
						color[0] = preprocessing_data.raw_data_3D_array[index1].at<float>(index2,0);
						color[1] = preprocessing_data.raw_data_3D_array[index1].at<float>(index2,1);
						color[2] = preprocessing_data.raw_data_3D_array[index1].at<float>(index2,2);

						DrawRectWithOpenGL(rect,color);
						delete(rect);

						y_position[1]+=35;
					}	
					*/
					
			}
			
			SwapOpenGLBuffers();
			
		}
		 
		System::Void DetailVisualization::DrawText_FTGL(float n,int x, int y, int r, int g, int b)
		{
			glPushMatrix();

			float font_size = 10*(scale_factor[2]+0.6+scale_x[2]);
			font.FaceSize(font_size);
			glColor3f(r, g, b);
			glRasterPos2f(x , y + font.LineHeight());
			stringstream ss;
			ss << n;
			string str = ss.str();
			text = (char*)str.c_str();
			font.Render(text);

			glPopMatrix();
		}

		System::Void DetailVisualization::DrawText_FTGL_Zero_Padding(float n,int x, int y, int r, int g, int b)
		{
			glPushMatrix();

			float font_size = 10*(scale_factor[2]+0.6+scale_x[2]);
			font.FaceSize(font_size);
			glColor3f(r, g, b);
			glRasterPos2f(x , y + font.LineHeight());
			stringstream ss;
			ss << n;
			string str = ss.str();
			char zero[] = "0";
			if(n<10)
			{
				strcat(zero,str.c_str());
				font.Render(zero);
			}
			else
			{
				text = (char*)str.c_str();
				font.Render(text);
			}
			glPopMatrix();
		}

		System::Void DetailVisualization::DrawTitle_FTGL(int t,int x, int y)
		{
			glPushMatrix();

			float font_size = 16*(scale_factor[2]+0.4+scale_x[2]);
			font.FaceSize(font_size);
			glColor3f(1.0, 1.0, 1.0);
			glRasterPos2f(x , y + font.LineHeight());
			font.Render(title[t]);

			glPopMatrix();			
		}

		System::Void DetailVisualization::title_string()
		{
			//strcpy(title[0],"住宅區 (進站)");
			//strcpy(title[1],"住宅區 (出站)");
			//strcpy(title[2],"辦公/學校 (進站)");
			//strcpy(title[3],"辦公/學校 (出站)");
			//strcpy(title[4],"觀光區 (進站)");
			//strcpy(title[5],"觀光區 (出站)");
			strcpy(title[0],"Residential (In)");
			strcpy(title[1],"Residential (Out)");
			strcpy(title[2],"Commercial/School (In)");
			strcpy(title[3],"Commercial/School (Out)");
			strcpy(title[4],"Tourism (In)");
			strcpy(title[5],"Tourism (Out)");
			//strcpy(title[0],"First Order of Distance");
			//strcpy(title[1],"Linear Acceleration");
			//strcpy(title[2],"Gravity");
			//strcpy(title[3],"Gyroscope");
		}

		System::Void DetailVisualization::DrawLine(int x1,int y1,int x2,int y2)
		{
			glPushMatrix();
			glLineWidth(2.0);
			glBegin(GL_LINES);
				glColor3f(1.0,1.0,1.0);
				glVertex3f(x1,y1,0.0);
				glVertex3f(x2,y2,0.0);
			glEnd();
			glPopMatrix();	
		}

		System::Void DetailVisualization::clear()
		{
			//raw_data_index.clear();
			raw_data_index_2D.clear();
		}
}