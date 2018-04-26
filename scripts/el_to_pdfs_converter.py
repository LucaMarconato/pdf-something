#!/usr/bin/env python3.6

# script for converting from the foram of easyLyceum to the new one (currently the .json format)

import os
import shutil
import sqlite3
import uuid
import datetime
import json
from collections import OrderedDict

global db_connection, db
global ovewrite_pdf

class Highlighting_component:
	def __init__(self, parent_highlighting_uuid, x1, y1, x2, y2):
		self.uuid = uuid.uuid4()
		self.parent_highlighting_uuid = parent_highlighting_uuid
		self.x1 = x1
		self.y1 = y1
		self.x2 = x2
		self.y2 = y2

class Highlighting:
	def __init__(self, uuid, defines_a_section, caption, marked_as_wrong, environment):
		self.uuid = uuid
		self.defines_a_section = defines_a_section
		self.caption = caption
		self.marked_as_wrong = marked_as_wrong
		self.environment = environment
		self.highlighting_components = dict()
		self.highlighting_components = set()

class Page:
	def __init__(self, page_number):
		self.uuid = uuid.uuid4()
		self.page_number = page_number
		self.highlighting_components = set()

class Document:
	def __init__(self, uuid, name, page_count, latest_opening, current_page, rows, columns):
		self.uuid = uuid
		self.name = name
		self.pages = [Page(i) for i in range(page_count)]
		# this is not precise to the seconds, so it cannot be used for real time synchronization
		delta = datetime.timedelta(11323, 7233, 653122)
		dt = datetime.datetime.utcfromtimestamp(latest_opening) + delta
		self.latest_opening = dt.strftime('%Y-%m-%d %H:%M:%S')
		self.highlightings = dict()
		self.current_page = current_page
		self.rows = rows
		self.columns = columns
	
	def add_highlighting_component(self,t,at_page):
		highlighting_uuid = t[0].lower()
		x1 = t[1]
		x2 = t[2]
		y1 = t[3]
		y2 = t[4]
		if x1 > x2:
			temp = x1
			x1 = x2
			x2 = temp
		if y1 > y2:
			temp = y1
			y1 = y2
			y2 = temp
		defines_a_section = bool(t[5])
		caption = str('' if t[6] == '_______________' else t[6]).encode('utf-8').decode('utf-8')
		marked_as_wrong = bool(t[7])
		environment = t[8]
		if environment == 'section':
			environment = 'black'
		elif environment == 'subsection':
			environment = 'gray'
		elif environment == 'text':
			environment = 'transparent'
		highlighting_component = Highlighting_component(highlighting_uuid, x1, y1, x2, y2)
		if not highlighting_uuid in self.highlightings:
			highlighting = Highlighting(highlighting_uuid,defines_a_section,caption,marked_as_wrong,environment)
			self.highlightings[highlighting_uuid] = highlighting
		self.highlightings[highlighting_uuid].highlighting_components.add(highlighting_component)
		self.pages[at_page].highlighting_components.add(highlighting_component)

def validate_json_string(s):
	data=json.loads(s, object_pairs_hook=OrderedDict)
	return data

# I am aware that I could have wrote this quickly with the json module, next time I will be lazier and use that
def convert_document(document):
	output_dir = '../frontends/canonical/data'
	if not os.path.exists(output_dir):
		os.makedirs(output_dir)
	if not os.path.exists(f'{output_dir}/{document.uuid}'):
		os.makedirs(f'{output_dir}/{document.uuid}')
	user_dir = os.path.expanduser('~')
	source_database_path = user_dir + '/Library/Application Support/easyLyceum/pdfs'
	src = source_database_path + '/' + document.uuid.upper()
	des = f'{output_dir}/{document.uuid}/document'
	shutil.copy2(src,des)

	s = '{\n'
	s += '"format":"pdf",\n'
	s += f'"uuid":"{document.uuid}",\n'
	s += f'"name":{json.dumps(document.name)},\n'
	s += f'"in_program_directory":"/",\n'
	s += f'"latest_opening":"{document.latest_opening}",\n'
	s += f'"current_index":{document.current_page},\n'
	s += '"grid_layout"\n:{\n'
	s += f'"rows":{document.rows},\n'
	s += f'"columns":{document.columns}\n'
	s += '},\n'
	s += '"pages":\n[\n'
	i = 0
	for page in document.pages:
		s += '{\n'
		s += f'"uuid":"{page.uuid}",\n'
		s += f'"index_in_pdf":{i},\n'
		s += '"highlighting_components":\n[\n'
		j = 0
		for hc in page.highlighting_components:
			s += f'"{hc.uuid}"'
			if j < len(page.highlighting_components)-1:
				s += ',\n'
			else:
				s += '\n'
			j += 1
		s += '],\n'
		s += '"crop":\n'
		s += '{\n"x0":0,\n"y0":0,\n"x1":1,\n"y1":1\n}\n'
		s += '}'
		if i < len(document.pages)-1:
			s += ',\n'
		else:
			s += '\n'
		i += 1
	s += '],\n'
	s += '"highlightings":\n[\n'
	i = 0
	for key, highlighting in document.highlightings.items():
		# integrity check
		if key != highlighting.uuid:
			print(f'fatal error: key = {key}, highlighting.uuid = {highlighting.uuid}')
			exit(1)
		s += '{\n'
		s += f'"uuid": "{highlighting.uuid}",\n'
		s += f'"color": "{highlighting.environment}",\n'
		s += f'"text": {json.dumps(highlighting.caption)}\n'
		s += '}'
		if i < len(document.highlightings)-1:
			s += ',\n'
		else:
			s += '\n'
		i += 1
	s += '],\n'
	s += '"highlighting_components":\n[\n'
	# i = 0
	first = True
	for page in document.pages:
		for hc in page.highlighting_components:
			if not first:
				s += ',\n'
			first = False
			s += '{\n'
			s += f'"uuid":"{hc.uuid}",\n'
			s += f'"parent_highlighting":"{hc.parent_highlighting_uuid}",\n'
			s += f'"x0":{hc.x1},\n'
			s += f'"y0":{hc.y1},\n'
			s += f'"x1":{hc.x2},\n'
			s += f'"y1":{hc.y2}\n'
			s += '}\n'
	s += '],\n'
	s += '"pages_ordering":\n[\n'
	i = 0
	for page in document.pages:
		s += '{\n'
		s += f'"uuid":"{page.uuid}",\n'
		s += '"ordering":\n{\n'
		prev_uuid = '' if i == 0 else document.pages[i-1].uuid
		next_uuid = '' if i == (len(document.pages)-1) else document.pages[i+1].uuid
		s += f'"prev": "{prev_uuid}",\n'
		s += f'"next": "{next_uuid}"\n'
		s += '}\n'
		s += '}'
		if i < len(document.pages)-1:
			s += ',\n'
		else:
			s += '\n'
		i += 1
	s += ']'
	s += '}'
	# so if the .json is wrong I can examine the file for understanding where the error is

	with open(f'{output_dir}/{document.uuid}/info.json','w') as outfile:
		print(s,file=outfile)

	data = validate_json_string(s)
	s = json.dumps(data, indent = 4, sort_keys = False)

	with open(f'{output_dir}/{document.uuid}/info.json','w') as outfile:
		print(s,file=outfile)

def open_database():
	global db_connection, db
	user_dir = os.path.expanduser('~')
	db_dir = user_dir + '/Library/Application Support/easyLyceum'
	db_connection = sqlite3.connect(db_dir + '/Highlightings.sqlite')
	db = db_connection.cursor()

def query(string):
	return db.execute(string).fetchall()

def close_database():
	db_connection.close();

def select_document(document_name):
	return query(f"SELECT * FROM ZPDF WHERE ZNAME LIKE '{document_name}'")

def page_count_for_document_id(document_id):
	return len(query(f"SELECT * FROM Z_4IN_PDF WHERE Z_5IN_PDF = '{document_id}'"))

def get_highlighting_components(page,document_id):
	query_string = f"SELECT "\
	f"ZUUID, ZX1.ZVALUE, ZX2.ZVALUE, ZY1.ZVALUE, ZY2.ZVALUE, ZHIGHLIGHTINGCOMPONENT.ZDEFINES_A_SECTION, ZCAPTION, ZMARKED_AS_WRONG, ZENVIRONMENT.ZNAME "\
	f"FROM "\
	f"ZHIGHLIGHTINGCOMPONENT, ZHIGHLIGHTING, ZENVIRONMENT, ZX1, ZX2, ZY1, ZY2 "\
	f"WHERE "\
	f"ZIN_PAGE = '{page}' AND ZIN_HIGHLIGHTING = ZHIGHLIGHTING.Z_PK AND ZIN_PDF = '{document_id}' AND ZIN_ENVIRONMENT = ZENVIRONMENT.Z_PK AND "\
	f"ZHIGHLIGHTINGCOMPONENT.ZX1 = ZX1.Z_PK AND "\
	f"ZHIGHLIGHTINGCOMPONENT.ZX2 = ZX2.Z_PK AND "\
	f"ZHIGHLIGHTINGCOMPONENT.ZY1 = ZY1.Z_PK AND "\
	f"ZHIGHLIGHTINGCOMPONENT.ZY2 = ZY2.Z_PK"

	# print(query_string)
	highlighting_components = query(query_string)
	return highlighting_components

def parse_document(t):
	document_id = t[0]
	document_uuid = t[12].lower()
	document_latest_opening = t[8]
	document_name = t[11]
	current_page = t[5]
	rows = t[6]
	columns = t[4]
	print(f'document_id = {document_id}, document_uuid = {document_uuid}, document_name = {document_name}, rows = {rows}, columns = {columns}, current_page = {current_page}')
	page_count = page_count_for_document_id(document_id)
	if page_count == 0:
		print(f'the document has {page_count} pages, skipping this document')
		return -1
	elif page_count > 1:
		print(f'the document has {page_count} pages')
	else:
		print(f'the document has {page_count} page')

	# for debugging with a small document
	# page_count = 1

	document = Document(document_uuid, document_name, page_count, document_latest_opening, current_page, rows, columns)

	i = 0
	for page in range(page_count):
		# the pages are 1 based in the easyLyceum database
		hcs = get_highlighting_components(page+1,document_id)
		# print(f'page {page} has {len(hcs)} highlighting components')		
		for hc in hcs:
			# the pages are 0 based in the new storage format
			document.add_highlighting_component(hc,page)
		i += 1
	return document

			
def tuple_from_document_name(document_name):
	result_list = select_document(document_name)
	if len(result_list) > 1:
		print(f'found {len(result_list)} documents, skipping this document')
		return -1
	elif len(result_list) == 0:
		print(f'no document found, skipping this document')
		return -1
	else:
		result = result_list[0]
		return result
		
open_database()
overwrite_pdf = False
print(f'overwrite_pdf = {overwrite_pdf}',
	  'overwrite_pdf = False: not overwriting the .pdf already present in the database, but overwriting the easyLyceum informations',
	  'overwrite_pdf = True:      overwriting the .pdf already present in the database, but overwriting the easyLyceum informations',
	  sep = '\n')
print('')
document_names = ['Luca Marconato - Appunti di statistica II [Pace]',
				  'geometria superiore modulo I',
				  'geometria superiore modulo II',
				  'weber',
				  'gorni',
				  'Patrick Gon - Appunti di statistica I',
				  'vidoni__Applied statistics and data analysis (labs theory)',
				  'vidoni__Applied statistics and data analysis (slides)',
				  'slides of algorithms for bioinformatics']
documents = []
for document_name in document_names:
	print(f'searching \'{document_name}\'')
	t = tuple_from_document_name(document_name)
	if t != -1:
		document = parse_document(t)
		if document != -1:
			documents.append(document)
	print('')

if len(documents) > 0:
	if len(documents) == 1:
		print('parsed 1 document, now converting it')
	else:
		print(f'parsed {len(documents)} documents, now converting them')

for document in documents:
	convert_document(document)
	print(f'converted {document.name}')
	
close_database()

