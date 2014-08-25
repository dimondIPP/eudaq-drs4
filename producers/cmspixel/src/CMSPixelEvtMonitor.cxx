#include "CMSPixelEvtMonitor.hh"
#include <TGClient.h>
#include <TGFrame.h>
#include <TClass.h>

using namespace std;



CMSPixelEvtMonitor* CMSPixelEvtMonitor::m_instance = NULL;


void CMSPixelEvtMonitor::DrawFromFile(std::string filename)
{
	std::ifstream file(filename);		
	if(!file.fail()){
		m_h2_map -> Clear();
		std::string line;
		while(std::getline(file, line))
		{
			std::stringstream   linestream(line);
			int                 col, row, value; 
			string							dummy;
			linestream >> dummy;
			while ((linestream.peek()!='\n') && (linestream >> col >> row >> value))
				m_h2_map -> Fill(col,row,value);
		}
		m_h2_map -> Draw("COLZ");
		m_canv -> Modified();
		m_canv -> Update();
	}
	else
		std::cout<<"Couldn't open file..."<<std::endl;
}



void CMSPixelEvtMonitor::DrawMap(std::vector<pxar::pixel> pixels, char* name)
{
	TH2D* h2_temp = new TH2D("h2_temp",Form("%s;col;row", name),52,-0.5,51.5,80,-0.5,79.5);
	for(std::vector<pxar::pixel>::iterator it = pixels.begin(); it != pixels.end(); ++it){
		int col = (int) it -> getColumn();
		int row = (int) it -> getRow();
		double value = it -> getValue();
		h2_temp -> Fill(col,row,value);
	} 
	m_canv -> cd() -> Clear();
	h2_temp -> Draw("colz");
	m_canv -> Modified();
	m_canv -> Update();
}

CMSPixelEvtMonitor::CMSPixelEvtMonitor()
{
	m_h2_map = new TProfile2D("m_h2_map","Hit Map;col;row",52,-0.5,51.5,80,-0.5,79.5);
	m_theApp = new TApplication("m_theApp",NULL,NULL);

	m_MF = new MyMainFrame( gClient->GetRoot(  ), 800, 600 );	
	
	m_canv = m_MF->GetCanvas(  );
	m_theApp -> SetReturnFromRun(true);
	gSystem -> ProcessEvents();
	gStyle -> SetOptStat(0);
}


MyMainFrame::MyMainFrame( const TGWindow * p, UInt_t w, UInt_t h )
:TGMainFrame( p, w, h )
{
  cout << "MyMainFrame..." << endl;
 // Create a main frame:
  fMain = new TGMainFrame( p, w, h );

 // Create canvas widget:
  fEcanvas = new TRootEmbeddedCanvas( "Ecanvas", fMain, w, h );
  fMain->AddFrame( fEcanvas, new TGLayoutHints( kLHintsExpandX | kLHintsExpandY, 1, 1, 1, 1 ) );

	fEcanvas->GetCanvas()->SetBorderMode(0);
	fEcanvas->GetCanvas()->SetBorderMode(0);
	fEcanvas->GetCanvas()->SetBit(kNoContextMenu);
	fEcanvas->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)",
			"TestDialog", this,
			"HandleEmbeddedCanvas(Int_t,Int_t,Int_t,TObject*)");

	
	
	GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)","PixTab",this, "UpdateCanvas(Int_t,Int_t,Int_t,TObject*)");




 // Set a name to the main frame:
  fMain->SetWindowName( "cmspixelProducer" );

 // Map all subwindows of main frame:
  fMain->MapSubwindows(  );

 // Initialize the layout algorithm:
  fMain->Resize( fMain->GetDefaultSize(  ) );

 // Map main frame:
  fMain->MapWindow(  );
}

MyMainFrame::~MyMainFrame(  )
{
 // Clean up used widgets: frames, buttons, layouthints
  fMain->Cleanup(  );
  delete fMain;
}

TCanvas *MyMainFrame::GetCanvas(  )
{
//TCanvas *c1 = fEcanvas->GetCanvas();
  return ( fEcanvas->GetCanvas(  ) );
}

void MyMainFrame::HandleEmbeddedCanvas(Int_t event, Int_t x, Int_t y,
		TObject *sel)
{
	// Handle events in the left embedded canvas.

	if (event == kButton3Down)
		printf("event = %d, x = %d, y = %d, obj = %s::%s\n", event, x, y,
				sel->IsA()->GetName(), sel->GetName());
}

